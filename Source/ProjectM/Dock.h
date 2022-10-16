// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dock.generated.h"

UCLASS()
class PROJECTM_API ADock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool bIsPlayerNearDock;
	bool bIsDocking;
	FVector vBoatDockLocation;
	FRotator rBoatDockRotation;
	float fDockingInterpSpeed;

	FVector vBoatUndockLocation;
	FRotator rBoatUndockRotation;
	float fUndockingInterpSpeed;

	void DockBoat();
	void UnDockBoat();

	
};
