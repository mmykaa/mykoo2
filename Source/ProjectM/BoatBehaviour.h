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


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) UStaticMeshComponent* boatMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<float> fSailSpeedByStage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TArray<float> fTurnSpeedByStage;

	void UpdateCameraBoomSettings();

	int iCurrentSailStage;
	bool bIsSailing;

	void SailsUp();
	void SailsDown();
	void Sail();
	void TurnSails(float inValue);
};
