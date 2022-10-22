// Fill out your copyright notice in the Description page of Project Settings.


#include "../WorldActors/Herb.h"

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

