// Fill out your copyright notice in the Description page of Project Settings.


#include "BoatBehaviour.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABoatBehaviour::ABoatBehaviour()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

void ABoatBehaviour::SailsUp()
{
	if (currentSailStage <= 0)
		return;

	--currentSailStage;
	UpdateBoatSpeed(currentSailStage);
}

void ABoatBehaviour::SailsDown()
{
	if (currentSailStage >= sailSpeedByStage.Num() - 1)
		return;

	++currentSailStage;
	UpdateBoatSpeed(currentSailStage);
}

void ABoatBehaviour::UpdateBoatSpeed(int& refSailStage)
{
	UCharacterMovementComponent* BoatCharacterMovement = GetCharacterMovement();

	BoatCharacterMovement->MaxWalkSpeed = sailSpeedByStage[refSailStage];
}

