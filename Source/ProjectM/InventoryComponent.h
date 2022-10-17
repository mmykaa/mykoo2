// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom) )
class PROJECTM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	TArray<UItem*> Inventory;

	void AddToInventory(UItem* InItem);
	
	
	bool bIsInteractingWithInventory;

	void OpenInventory();
	void CloseInventory();

	int iOneLeftSlot;
	int iTwoLeftSlot;
	int iCurrentSlotSelected;
	int iOneRightSlot;
	int iTwoRightSlot;

	void HandlePositiveOverflow(int& SlotToHandle);

	void HandleNegativeOverflow(int& SlotToHandle);


	void CycleLeft();
	void CycleRight();
	
};
