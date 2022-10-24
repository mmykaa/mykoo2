// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/InputComponent.h>
#include "ProjectM/Components/HealthComponent.h"
#include "ProjectM/Components/StatsComponent.h"
#include "../Components/InventoryComponent.h"
#include "PlayerBehaviour.generated.h"

UCLASS(config=Game)
class APlayerBehaviour : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APlayerBehaviour();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface


#pragma region Controls

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

#pragma endregion Controls

#pragma region Locomotion


	bool bMovingForward;
	bool bMovingBack;
	bool bMovingLeft;
	bool bMovingRight;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) bool bIsMoving;
	float moveRightDegrees;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) float fMoveDirection;

	void SetMoveSpeed();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) float CurrentInclination;
	float MaxInclination;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) float InclinationSpeed;
	void UpdateInclination();
	float MathToward(float inFloatOne, float inFloatTwo, float Value);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  float fInputDirection;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  float fInputMoveStart;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  bool bStartWalkEnded;
	void UpdateMoveState();
	float GetRelativeDirection();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  float fMoveSpeed;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  bool bIsSprinting;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  bool bIsRunning;
	void StartRunning();
	void StopRunning();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) bool bIsInAir;
	void StartJump();

	void ToggleWalk();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)  bool bIsWalking;

	bool bCanJump;

#pragma endregion Locomotion

#pragma region Camera

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma endregion Camera

#pragma region SwitchCharacters

	void SwitchCharacter();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) ACharacter* BoatCharacter;

	void SetUnique();
	AActor* Uniques;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) TSubclassOf<AActor> UniquesHelperClass;

#pragma endregion SwitchCharacters

#pragma region Components

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UInventoryComponent* InventoryComponent;
	UInventoryComponent* GetInventoryComponent();
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) UStatsComponent* StatsComponent;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere) UHealthComponent* HealthSystem;

	 
#pragma endregion Components
	
#pragma region Interations
public:

	void InventoryOpen() { Cast<UInventoryComponent>(InventoryComponent)->OpenInventory(); }
	void InventoryClose() { Cast<UInventoryComponent>(InventoryComponent)->CloseInventory(); }
	void InventoryCycleRight() { Cast<UInventoryComponent>(InventoryComponent)->CycleRight(); }
	void InventoryCycleLeft() { Cast<UInventoryComponent>(InventoryComponent)->CycleLeft(); }


	TArray<AActor*> InteractablesQueue;
	
	void AddInteractableToQueue(AActor* inActor);
	void RemoveInteractableFromQueue(AActor* inActor);
	void Interact();
	bool CanInteract();

#pragma endregion Interations

};

