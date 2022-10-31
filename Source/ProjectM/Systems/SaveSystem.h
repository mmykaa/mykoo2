// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveSystem.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTM_API USaveSystem : public USaveGame
{
	GENERATED_BODY()

		USaveSystem();

public:
	UPROPERTY(EditAnywhere) FVector PlayerPosition;
	UPROPERTY(EditAnywhere) FRotator PlayerRotation;

	UPROPERTY(EditAnywhere) int PlayerCurrentHealth;
	UPROPERTY(EditAnywhere) int PlayerMaxHealth;

	void Save();

	void Load();


};
