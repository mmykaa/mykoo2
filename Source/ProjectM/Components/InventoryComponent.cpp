// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Controllers/PlayerBehaviour.h"

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
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < DefaultInventoryItems.Num(); ++i)
	{
		UItem* m_TempItem =  NewObject<UItem>(this, DefaultInventoryItems[i]);

		if (!m_TempItem) return;
		
		Inventory.Add(m_TempItem);
		UE_LOG(LogTemp, Warning, TEXT("ITEM: %s"), * m_TempItem->GetName());
	}

}

void UInventoryComponent::AddToInventory(TSubclassOf<UItem> inItem)
{
	//TO DO CHeck if already exists

	UE_LOG(LogTemp, Warning, TEXT("ADDINT ITEM: %s"), *inItem->GetName());

	if (!inItem) return;
	

	if (!CheckIfItemExists(inItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("ITEM: %s"), *inItem->GetName());
		UE_LOG(LogTemp, Warning, TEXT("DONT EXIST"));

		UItem* m_TempItem = NewObject<UItem>(this, inItem);

		if (!m_TempItem) return;

		

		Inventory.Add(m_TempItem);

		if (Cast<APlayerBehaviour>(GetOwner()))
		{
			Cast<APlayerBehaviour>(GetOwner())->RefreshInventoryWidget();
		}
	}
	else if(CheckIfItemExists(inItem))
	{

		UE_LOG(LogTemp, Warning, TEXT("ITEM: %s"), *inItem->GetName());
		UE_LOG(LogTemp, Warning, TEXT("EXIST"));

		UItem* m_ItemToStack = Inventory[iItemIndex];

		//Check if the item can Stack
		if (!Cast<UItem>(m_ItemToStack)->GetCanStack())
		{
			return;
		}
		else
		{
			//Get the amount to stack over the existing item
			int m_ItemAmountToStack = Cast<UItem>(inItem)->GetAmountItemAmount();
			Inventory[iItemIndex]->AddAmount(m_ItemAmountToStack);

			if (Cast<APlayerBehaviour>(GetOwner()))
			{
				Cast<APlayerBehaviour>(GetOwner())->RefreshInventoryWidget();
			}
		}
	}
	
}

bool UInventoryComponent::CheckIfItemExists(TSubclassOf<UItem> inItem)
{
	bool m_bItemExists = false;
	
	for (int i = 0; i < Inventory.Num(); ++i)
	{
		if (Inventory[i]->GetClass() == inItem)
		{
			iItemIndex = i;
			m_bItemExists = true;
			break;
		}
	}

	return m_bItemExists;
}

void UInventoryComponent::RemoteFromInventory(TSubclassOf<UItem> inItem)
{

}

void UInventoryComponent::OpenInventory()
{
 	bIsInteractingWithInventory = true;
}

void UInventoryComponent::CloseInventory()
{
	bIsInteractingWithInventory = false;
}

void UInventoryComponent::CycleRight()
{

	if (bIsInteractingWithInventory)
	{
		if (DefaultInventoryItems.Num() >= 5)
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
	if (SlotToHandle > DefaultInventoryItems.Num()-1)
	{
		SlotToHandle = 0;
	}
}


void UInventoryComponent::CycleLeft()
{
	if (bIsInteractingWithInventory)
	{
		if (DefaultInventoryItems.Num() >= 5)
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
		SlotToHandle = DefaultInventoryItems.Num() -1;
	}
}

