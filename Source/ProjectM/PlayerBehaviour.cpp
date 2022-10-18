// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerBehaviour.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UniquesHelper.h"
#include <Kismet/GameplayStatics.h>
#include "InventoryComponent.h"
#include "HealthComponent.h"


//////////////////////////////////////////////////////////////////////////
// AProjectMCharacter


#define Print(x) if(GEngine){GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Yellow, TEXT(x));}

APlayerBehaviour::APlayerBehaviour()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
	
	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
	HealthSystem = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	bIsRunning = true;
	MaxInclination = 45.0f;
	InclinationSpeed = 60.0f;
	fMoveSpeed = 2;
}


void APlayerBehaviour::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerBehaviour::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerBehaviour::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerBehaviour::StopRunning);
	PlayerInputComponent->BindAction("ToggleWalk", IE_Pressed, this, &APlayerBehaviour::ToggleWalk);

	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &APlayerBehaviour::SwitchCharacter);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerBehaviour::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerBehaviour::MoveRight);

	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &APlayerBehaviour::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &APlayerBehaviour::LookUpAtRate);

	PlayerInputComponent->BindAction("InventoryToggle", IE_Pressed, this, &APlayerBehaviour::InventoryOpen);
	PlayerInputComponent->BindAction("InventoryToggle", IE_Released, this, &APlayerBehaviour::InventoryClose);

	PlayerInputComponent->BindAction("InventoryCyclePositive", IE_Pressed, this, &APlayerBehaviour::InventoryCycleRight);
	PlayerInputComponent->BindAction("InventoryCycleNegative", IE_Pressed, this, &APlayerBehaviour::InventoryCycleLeft);
}


void APlayerBehaviour::BeginPlay()
{
	Super::BeginPlay();
	fMoveSpeed = FMath::FInterpTo(fMoveSpeed,0.1f,GetWorld()->GetDeltaSeconds(),2.0f);
	SetUnique();
}

void APlayerBehaviour::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateMoveState();
	UpdateInclination();
	bIsInAir = GetCharacterMovement()->IsFalling();	
}


void APlayerBehaviour::SwitchCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING TO SWAP TO BOAT"));
	AActor* BoatActor = Cast<AUniquesHelper>(Uniques)->GetBoatUnique();
	BoatCharacter = Cast<ACharacter>(BoatActor);

	if (BoatCharacter != nullptr && GetController())
	{
		AController* temp = GetController();
		
		if (temp)
		{
			temp->UnPossess();
			temp->Possess(BoatCharacter);
			UE_LOG(LogTemp, Warning, TEXT("BOAT"));

		}
	}
}

void APlayerBehaviour::SetUnique()
{
	if (!UniquesHelperClass)
		return;


	Uniques = UGameplayStatics::GetActorOfClass(GetWorld(), UniquesHelperClass);

	Cast<AUniquesHelper>(Uniques)->SetPlayerUnique(this);
}

void APlayerBehaviour::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerBehaviour::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerBehaviour::MoveForward(float Value)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	}
	
	if(Value == 0.0f)
	{
		bMovingForward = false;
		bMovingBack = false;
	}
	if (Value > 0.0f)
	{
		bMovingForward = true;
		bMovingBack = false;
		SetMoveSpeed();
	}
	if (Value < 0.0f)
	{
		bMovingForward = false;
		bMovingBack = true;
		SetMoveSpeed();
	}
}

void APlayerBehaviour::MoveRight(float Value)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	}

	if(Value == 0.0f)
	{
		bMovingRight = false;
		bMovingLeft = false;
	}
	if (Value > 0.0f)
	{
		bMovingRight = true;
		bMovingLeft = false;
		SetMoveSpeed();
	}
	if (Value < 0.0f)
	{
		bMovingRight = false;
		bMovingLeft = true;
		SetMoveSpeed();
	}
}

float APlayerBehaviour::GetRelativeDirection()
{
	fMoveDirection = GetControlRotation().Yaw;
	
	float fMoveFBSum;
	float fMoveRLSum;
	
	float fCovFoward = UKismetMathLibrary::Conv_BoolToFloat(bMovingForward);
	float fCovBack = UKismetMathLibrary::Conv_BoolToFloat(bMovingBack);
	float fCovRight = UKismetMathLibrary::Conv_BoolToFloat(bMovingRight);
	float fCovLeft = UKismetMathLibrary::Conv_BoolToFloat(bMovingLeft);

	fMoveFBSum = fCovFoward + (fCovBack * -1);
	fMoveRLSum = fCovRight + (fCovLeft * -1);

	//If Player moves FWD or BWD multiply RGT/LFT by 0.5
	
	if (fMoveRLSum != 0) 
	{
		moveRightDegrees = 1.0f;

		if ((!bMovingForward && !bMovingBack) && (bMovingRight || bMovingLeft))
		{
			moveRightDegrees = 1.0f;
		}

		if ((bMovingForward || bMovingBack) && (bMovingRight || bMovingLeft))
		{
			moveRightDegrees = 0.5f;
		}
	}
	else
	{
		moveRightDegrees = 1.0f;
	}
	
	if (fMoveFBSum < 0) // == -1
	{
		moveRightDegrees *= -1;
		
		//Player want bwd 180
		fMoveDirection += 180;
	}
	
	//Player want right 90 degrees multiplier
	if (fMoveRLSum > 0) // == 1
	{
		fMoveDirection = (fMoveDirection + (moveRightDegrees * 90));

	}
	
	//Player want left 90 degrees multiplier
	if (fMoveRLSum < 0) // == -1
	{
		fMoveDirection =  (fMoveDirection + (moveRightDegrees * -90)) ;
	}

	FRotator rDirection = FRotator(0.0f, fMoveDirection, 0.0f);

	FRotator NormalizedDeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(rDirection, GetActorRotation());

	
	fMoveDirection = NormalizedDeltaRot.Yaw;
	
	return fMoveDirection;
}

void APlayerBehaviour::StartRunning()
{
	bIsSprinting = true;
	bIsRunning = false;
	bIsWalking = false;
	fMoveSpeed = FMath::FInterpTo(fMoveSpeed,3,GetWorld()->GetDeltaSeconds(),20.0f);
}

void APlayerBehaviour::StopRunning()
{
	bIsSprinting = false;
	bIsRunning = true;
	bIsWalking = false;
	fMoveSpeed = FMath::FInterpTo(fMoveSpeed,2,GetWorld()->GetDeltaSeconds(),1.0f);
}

void APlayerBehaviour::StartJump()
{
	if (!bCanJump)
		return;

	this->ACharacter::Jump();
	bIsInAir = true;
}

void APlayerBehaviour::ToggleWalk()
{
	if(!bIsWalking)
	{
		bIsWalking = true;
		bIsRunning = false;
	}
	else
	{
		bIsWalking = false;
		bIsRunning = true;
	}
}

void APlayerBehaviour::SetMoveSpeed()
{
	if (!bIsWalking && !bIsRunning && bIsSprinting)
	{
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed,3,GetWorld()->GetDeltaSeconds(),20.0f);
		GetCharacterMovement()->JumpZVelocity = 350.f;
	}
	if (!bIsWalking && bIsRunning && !bIsSprinting)
	{
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed,2,GetWorld()->GetDeltaSeconds(),20.0f);
		GetCharacterMovement()->JumpZVelocity = 350.f;
	}
	if (bIsWalking && !bIsRunning && !bIsSprinting)
	{
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed,1,GetWorld()->GetDeltaSeconds(),20.0f);
		GetCharacterMovement()->JumpZVelocity = 400.f;
	}
}

void APlayerBehaviour::UpdateInclination()
{
	if (bStartWalkEnded && bIsMoving)
	{
		float TowardValue = MathToward(CurrentInclination, fMoveDirection, InclinationSpeed * GetWorld()->GetDeltaSeconds());
		CurrentInclination = FMath::Clamp(TowardValue, MaxInclination * -1, MaxInclination);
	}
}

float APlayerBehaviour::MathToward(float inFloatOne, float inFloatTwo, float Value)
{
	bool bWasLower;
	float NewValue;
	if (inFloatOne > inFloatTwo)
	{
		bWasLower = false;
		NewValue = inFloatOne - Value;

		if (inFloatTwo > Value )
		{
			NewValue = inFloatOne - Value;
		}
	}

	if (inFloatOne < inFloatTwo)
	{
		bWasLower = true;
		NewValue = 	inFloatOne + Value;
		
		if (NewValue > inFloatTwo)
		{
			NewValue = inFloatTwo;
		}
	}
	else
	{
		NewValue = inFloatTwo;
	}
	

	return NewValue;
}

void APlayerBehaviour::UpdateMoveState()
{
	if (bMovingForward || bMovingBack || bMovingRight || bMovingLeft)
	{
		bIsMoving = true;
		bCanJump = true;

	}

	if (!bMovingForward && !bMovingBack  && !bMovingRight  && !bMovingLeft)
	{
		bIsMoving = false;
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed,0.1f,GetWorld()->GetDeltaSeconds(),2.0f);
		bCanJump = false;

	}

	if (bStartWalkEnded)
	{
		fInputDirection = GetRelativeDirection();
		fInputMoveStart = GetRelativeDirection();
	}
	else
	{
		fInputDirection = GetRelativeDirection();
	}

	
}
