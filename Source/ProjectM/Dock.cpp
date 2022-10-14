// Fill out your copyright notice in the Description page of Project Settings.


#include "Dock.h"

// Sets default values
ADock::ADock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADock::DockBoat()
{
	//when docking move the boat to the dock location and then rotate it to the desired location
}

