// Fill out your copyright notice in the Description page of Project Settings.


#include "../WorldActors/Herb.h"
#include "../Controllers/PlayerBehaviour.h"
#include "../Components/InventoryComponent.h"
#include "../Items/Base/Item.h"


// Sets default values
AHerb::AHerb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHerb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHerb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHerb::Harvest()
{
	bIsHarverted = true;
	GetWorld()->GetTimerManager().SetTimer(HarvestTimer,this, &AHerb::Restock, fTimeBeetweenRestock, false, 0.0f);
}

void AHerb::Restock()
{
	bIsHarverted = false;
}


void AHerb::OnPlayerOverlapBegin(AActor* OtherActor)
{
	PlayerActor = OtherActor;
	APlayerBehaviour* m_Player = Cast<APlayerBehaviour>(OtherActor);
	m_Player->AddInteractableToQueue(this);
}


void AHerb::OnPlayerOverlapEnd(AActor* OtherActor)
{
	PlayerActor = OtherActor;
	APlayerBehaviour* m_Player = Cast<APlayerBehaviour>(PlayerActor);
	m_Player->RemoveInteractableFromQueue(this);
}

		
void AHerb::OnInteract()
{
	UInventoryComponent* PlayerIventory = Cast<APlayerBehaviour>(PlayerActor)->GetInventoryComponent();
	
	if (PlayerIventory != nullptr)
	{
		PlayerIventory->AddToInventory(ItemToDrop);
	}
	
}
