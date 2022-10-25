// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectM/Items/Base/Item.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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

	UPROPERTY(BlueprintAssignable) FOnInventoryUpdated OnInventoryUpdated;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)	TArray<TSubclassOf<UItem>> DefaultInventoryItems;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) TArray<UItem*> Inventory;

	UFUNCTION() void AddToInventory(TSubclassOf<UItem> inItem);
	UFUNCTION() void RemoteFromInventory(TSubclassOf<UItem> inItem);


	bool CheckIfItemExists(TSubclassOf<UItem> inItem);
	int iItemIndex;
	TArray<UItem*> GetInventoryCopy() { return Inventory; }
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
