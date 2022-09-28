// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BoatBehaviour.generated.h"

UCLASS()
class PROJECTM_API ABoatBehaviour : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoatBehaviour();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadWrite) UStaticMeshComponent* boatMesh;

	UPROPERTY(BlueprintReadWrite) TArray<float> sailSpeedByStage;

	int currentSailStage;

	void SailsUp();
	void SailsDown();
	void Sail();
	void UpdateBoatSpeed(int& sailStage);
	void TurnSails(float inValue);
};
