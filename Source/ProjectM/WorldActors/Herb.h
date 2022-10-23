// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/BoxComponent.h>
#include "InteractableActor.h"
#include "Herb.generated.h"

UCLASS()
class PROJECTM_API AHerb : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHerb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<UObject> ItemToDrop;

	bool bIsHarverted;

	TSubclassOf<AActor> Player;

	void Harvest();
	FTimerHandle HarvestTimer;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float fTimeBeetweenRestock;
	void Restock();
	
	virtual void OnPlayerOverlapBegin(AActor* OtherActor) override;
	virtual void OnPlayerOverlapEnd(AActor* OtherActor) override;
};
