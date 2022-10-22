// Fill out your copyright notice in the Description page of Project Settings.


#include "UniquesHelper.h"

// Sets default values
AUniquesHelper::AUniquesHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUniquesHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUniquesHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUniquesHelper::SetPlayerUnique(AActor* InPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING Player SET"));

	if (InPlayer != nullptr)
	{
		UniquePlayer = InPlayer;
		UE_LOG(LogTemp, Warning, TEXT("Player SET"));
	}
}

AActor* AUniquesHelper::GetPlayerUnique()
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING Player GET"));

	if (!UniquePlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerUnique Failed"));
		return nullptr;
	}


	return UniquePlayer ;
}



void AUniquesHelper::SetBoatUnique(AActor* InBoat)
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING BOAT SET"));

	if (InBoat != nullptr)
	{
		UniqueBoat = InBoat;
		UE_LOG(LogTemp, Warning, TEXT("BOAT SET"));

	}
}

AActor* AUniquesHelper::GetBoatUnique()
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING Boat GET"));

	if (!UniqueBoat)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoatUnique Failed"));
		return nullptr;
	}

	return UniqueBoat;
}
