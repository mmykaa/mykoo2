// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTM_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int iStatsDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int iStatsDefence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int iStatsHealth;

public:
	int GetStatsDamage() { return iStatsDamage; }
	int GetStatsDefence() { return iStatsDefence; }
	int GetStatsHealth() { return iStatsHealth; }

	void SetStatsHealth(int inStatsHealth) { iStatsHealth = inStatsHealth; }

};
