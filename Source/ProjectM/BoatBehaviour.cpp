// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatBehaviour.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"  
#include "Components/CapsuleComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include "UniquesHelper.h"

// Sets default values
ABoatBehaviour::ABoatBehaviour()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	boatMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoatMesh");
	boatMesh->SetupAttachment(RootComponent);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(boatMesh);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ABoatBehaviour::BeginPlay()
{
	Super::BeginPlay();
	SetUnique();
}

// Called every frame
void ABoatBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Sail();

}

// Called to bind functionality to input
void ABoatBehaviour::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("BoatSailsUp", IE_Pressed, this, &ABoatBehaviour::SailsUp);
	PlayerInputComponent->BindAction("BoatSailsDown", IE_Pressed, this, &ABoatBehaviour::SailsDown);
	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &ABoatBehaviour::SwitchCharacter);

	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABoatBehaviour::TurnSails);
}


void ABoatBehaviour::SetUnique()
{
	if (!UniquesHelperClass) 
		return;

	Uniques = UGameplayStatics::GetActorOfClass(GetWorld(), UniquesHelperClass);

	Cast<AUniquesHelper>(Uniques)->SetBoatUnique(this);
}

void ABoatBehaviour::UpdateCameraBoomSettings()
{

	if (iCurrentSailStage == 0)
	{
		CameraBoom->CameraLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagSpeed, 3.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraRotationLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraRotationLagSpeed, 3.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraLagMaxDistance = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagMaxDistance, 100.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
	}

	if (iCurrentSailStage == 1)
	{
		CameraBoom->CameraLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagSpeed, 2.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraRotationLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraRotationLagSpeed, 2.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraLagMaxDistance = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagMaxDistance, 200.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
	}

	if (iCurrentSailStage == 2)
	{
		CameraBoom->CameraLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagSpeed, 1.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraRotationLagSpeed = UKismetMathLibrary::FInterpTo(CameraBoom->CameraRotationLagSpeed, 1.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
		CameraBoom->CameraLagMaxDistance = UKismetMathLibrary::FInterpTo(CameraBoom->CameraLagMaxDistance, 300.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
	}
}

void ABoatBehaviour::SwitchCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING TO SWAP TO Player"));

	AActor* PlayerActor = Cast<AUniquesHelper>(Uniques)->GetPlayerUnique();
	PlayerCharacter = Cast<ACharacter>(PlayerActor);

	if (PlayerCharacter != nullptr && GetController())
	{
		AController* temp = GetController();

		if (temp)
		{
			temp->UnPossess();
			temp->Possess(PlayerCharacter);
			UE_LOG(LogTemp, Warning, TEXT("PLAYER"));

		}
	}
}

void ABoatBehaviour::SailsUp()
{
	if (iCurrentSailStage <= 0)
		return;

	--iCurrentSailStage;
	UpdateCameraBoomSettings();
}

void ABoatBehaviour::SailsDown()
{
	if (iCurrentSailStage >= fSailSpeedByStage.Num() - 1)
		return;

	++iCurrentSailStage;
	UpdateCameraBoomSettings();

}

void ABoatBehaviour::Sail()
{
	if (iCurrentSailStage <= 0)
		return;

	// Apply the force only in the X and Y

	this->GetCapsuleComponent()->AddForceAtLocation(FVector(GetActorForwardVector().X * fSailSpeedByStage[iCurrentSailStage],
		GetActorForwardVector().Y * fSailSpeedByStage[iCurrentSailStage],0), this->GetCapsuleComponent()->GetCenterOfMass());

}

void ABoatBehaviour::TurnSails(float inValue)
{
	if ((Controller != nullptr))
	{
		//Get Sail Mesh
		//Add Rotation to the mesh
		
		FHitResult hitResult;
		this->K2_AddActorWorldRotation(FRotator(0, fTurnSpeedByStage[iCurrentSailStage] * inValue,0) ,false, hitResult,false);
	}
}

