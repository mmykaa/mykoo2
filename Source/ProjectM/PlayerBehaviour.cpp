// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerBehaviour.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 


	MaxInclination = 45.0f;
	InclinationSpeed = 60.0f;
	fMoveSpeed = 2;
}


void APlayerBehaviour::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerBehaviour::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerBehaviour::StopRunning);

	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &APlayerBehaviour::SwitchCharacter);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerBehaviour::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerBehaviour::MoveRight);

	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &APlayerBehaviour::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &APlayerBehaviour::LookUpAtRate);


}

void APlayerBehaviour::SwitchCharacter()
{
	if (OtherCharacter != nullptr && GetController())
	{
		AController* temp = GetController();
		
		if (temp)
		{
			temp->UnPossess();
			temp->Possess(OtherCharacter);
		}
	}
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

void APlayerBehaviour::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateMoveState();
	UpdateInclination();

	// if (bIsHoldingSprint)
	// {
	// 	StartRunning();
	// }
	// else
	// {
	// 	StopRunning();
	// }
	
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
	}
	if (Value < 0.0f)
	{
		bMovingForward = false;
		bMovingBack = true;
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
	}
	if (Value < 0.0f)
	{
		bMovingRight = false;
		bMovingLeft = true;
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

	UE_LOG(LogTemp, Warning, TEXT("RLSUM: %f"), fMoveRLSum);

	if (fMoveRLSum != 0) 
	{
		moveRightDegrees = 1.0f;

		/// TO REMOVE
		if ((!bMovingForward && !bMovingBack) && (bMovingRight || bMovingLeft))
		{
			moveRightDegrees = 1.0f;
		}

		if ((bMovingForward || bMovingBack) && (bMovingRight || bMovingLeft))
		{
			moveRightDegrees = 0.5f;
		}
		/// TO REMOVE

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
	if (bIsHoldingSprint)
	{
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed, 2, GetWorld()->GetDeltaSeconds(), 10.0f);
	}
	else
	{
		bIsHoldingSprint = true;
	}
}

void APlayerBehaviour::StopRunning()
{
	if (!bIsHoldingSprint)
	{
		fMoveSpeed = FMath::FInterpTo(fMoveSpeed, 0, GetWorld()->GetDeltaSeconds(), 10.0f);
	}
	else
	{
		bIsHoldingSprint = false;
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
	}

	if (!bMovingForward && !bMovingBack  && !bMovingRight  && !bMovingLeft)
	{
		bIsMoving = false;
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
