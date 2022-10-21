// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int iMaxHealth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) int iCurrentHealth;
	UPROPERTY() int iDefence;

	void TakeDamage(int inDamageAmount);
	void Heal(int inHealAmount);
	void IncreaseMaxHealth(int inIncreaseAmount);
	void DecreaseMaxHealth(int inDecreaseAmount);

	UPROPERTY()	UStatsComponent* StatsComponent;

	void GetBaseStats(UStatsComponent* inStatsComponent);
	void SetBaseHealth();
	void UpdateStatsHealth();
};
