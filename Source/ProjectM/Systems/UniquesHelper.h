// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UniquesHelper.generated.h"

UCLASS()
class PROJECTM_API AUniquesHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUniquesHelper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* UniquePlayer;
	void SetPlayerUnique(AActor* InPlayer);
	AActor* GetPlayerUnique();

	AActor* UniqueBoat;
	void SetBoatUnique(AActor* InBoat);
	AActor* GetBoatUnique();

};
