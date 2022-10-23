// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	iTwoLeftSlot = 0;
	iOneLeftSlot = 1;
	iCurrentSlotSelected = 2;
	iOneRightSlot = 3;
	iTwoRightSlot = 4;

	Inventory.SetNum(5);
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInventoryComponent::OpenInventory()
{
 	bIsInteractingWithInventory = true;
	UE_LOG(LogTemp, Warning, TEXT("OPEN"));
}

void UInventoryComponent::CloseInventory()
{
	bIsInteractingWithInventory = false;
	UE_LOG(LogTemp, Warning, TEXT("CLOSE"));

}

void UInventoryComponent::CycleRight()
{

	if (bIsInteractingWithInventory)
	{
		if (Inventory.Num() >= 5)
		{
			UE_LOG(LogTemp, Warning, TEXT("RIGHT"));

			++iTwoLeftSlot;
			HandlePositiveOverflow(iTwoLeftSlot);
			UE_LOG(LogTemp, Warning, TEXT("TL: %d"), iTwoLeftSlot);

			++iOneLeftSlot;
			HandlePositiveOverflow(iOneLeftSlot);
			UE_LOG(LogTemp, Warning, TEXT("OL: %d"), iOneLeftSlot);

			++iCurrentSlotSelected;
			HandlePositiveOverflow(iCurrentSlotSelected);
			UE_LOG(LogTemp, Warning, TEXT("CS: %d"), iCurrentSlotSelected);

			++iOneRightSlot;
			HandlePositiveOverflow(iOneRightSlot);
			UE_LOG(LogTemp, Warning, TEXT("OR: %d"), iOneRightSlot);

			++iTwoRightSlot;
			HandlePositiveOverflow(iTwoRightSlot);
			UE_LOG(LogTemp, Warning, TEXT("TR: %d"), iTwoRightSlot);
		}
	}
}

void UInventoryComponent::HandlePositiveOverflow(int& SlotToHandle)
{
	if (SlotToHandle > Inventory.Num()-1)
	{
		SlotToHandle = 0;
	}
}


void UInventoryComponent::CycleLeft()
{
	if (bIsInteractingWithInventory)
	{
		if (Inventory.Num() >= 5)
		{
			UE_LOG(LogTemp, Warning, TEXT("LEFT"));

			--iTwoLeftSlot;
			HandleNegativeOverflow(iTwoLeftSlot);
			UE_LOG(LogTemp, Warning, TEXT("TL: %d"), iTwoLeftSlot);

			--iOneLeftSlot;
			HandleNegativeOverflow(iOneLeftSlot);
			UE_LOG(LogTemp, Warning, TEXT("OL: %d"), iOneLeftSlot);

			--iCurrentSlotSelected;
			HandleNegativeOverflow(iCurrentSlotSelected);
			UE_LOG(LogTemp, Warning, TEXT("CS: %d"), iCurrentSlotSelected);

			--iOneRightSlot;
			HandleNegativeOverflow(iOneRightSlot);
			UE_LOG(LogTemp, Warning, TEXT("OR: %d"), iOneRightSlot);

			--iTwoRightSlot;
			HandleNegativeOverflow(iTwoRightSlot);
			UE_LOG(LogTemp, Warning, TEXT("TR: %d"), iTwoRightSlot);
		}
	}
}


void UInventoryComponent::HandleNegativeOverflow(int& SlotToHandle)
{
	if (SlotToHandle < 0)
	{
		SlotToHandle = Inventory.Num() -1;
	}
}

