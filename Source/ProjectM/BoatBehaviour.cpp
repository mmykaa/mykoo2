// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatBehaviour.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"  
#include "Components/CapsuleComponent.h"

// Sets default values
ABoatBehaviour::ABoatBehaviour()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boatMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoatMesh");
	SetRootComponent(boatMesh);
}

// Called when the game starts or when spawned
void ABoatBehaviour::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoatBehaviour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoatBehaviour::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("BoatSailsUp", IE_Pressed, this, &ABoatBehaviour::SailsUp);
	PlayerInputComponent->BindAction("BoatSailsDown", IE_Pressed, this, &ABoatBehaviour::SailsDown);

	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABoatBehaviour::TurnSails);


}

void ABoatBehaviour::SailsUp()
{
	if (currentSailStage <= 0)
		return;

	--currentSailStage;
}

void ABoatBehaviour::SailsDown()
{
	if (currentSailStage >= sailSpeedByStage.Num() - 1)
		return;

	++currentSailStage;
}

void ABoatBehaviour::Sail()
{
	if (currentSailStage <= 0)
		return;


	this->GetCapsuleComponent()->AddForceAtLocation(FVector(sailSpeedByStage[currentSailStage], sailSpeedByStage[currentSailStage],0),
												this->GetCapsuleComponent()->GetCenterOfMass());

	// Apply the force only in the X and Y

}

void ABoatBehaviour::TurnSails(float inValue)
{
	if ((Controller != nullptr) && (inValue != 0.0f))
	{
		//Get Sail Mesh
		//Add Rotation to the mesh
		// Apply the force only in the X and Y
	}
}

