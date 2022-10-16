// Fill out your copyright notice in the Description page of Project Settings.


#include "Dock.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ADock::ADock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	fDockingInterpSpeed = 1.0f;
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
	
	//if is the first time arriving to the island
		// Play Cinematic
		// display Island Title
	
	//if is not the first time
		//Display Island Title

	//unpossess the boat, possess the player
	//when docking move the boat to the dock location and then rotate it to the desired location
	bIsDocking = true;
	FVector vDockingInterpPosition = UKismetMathLibrary::VInterpTo(this->GetActorLocation(), vBoatDockLocation, 
									GetWorld()->GetDeltaSeconds(), fDockingInterpSpeed);

	FRotator rDockingInterpRotation = UKismetMathLibrary::RInterpTo(this->GetActorRotation(), rBoatDockRotation,
		GetWorld()->GetDeltaSeconds(), fDockingInterpSpeed);


	this->SetActorLocation(vDockingInterpPosition);
	this->SetActorRotation(rDockingInterpRotation);

	//disable lola tracking

}

void ADock::UnDockBoat()
{
	//enable lola tracking
	
	//focus lola and wait for the player to input the next travel destiny
	//give Lola an the destiny that the player wants
	 
	//display text "sailing to open seas"

	//undock boat
	FVector vUndockingInterpPosition = UKismetMathLibrary::VInterpTo(this->GetActorLocation(), vBoatUndockLocation, 
									GetWorld()->GetDeltaSeconds(), fUndockingInterpSpeed);

	FRotator rUndockingInterpRotation = UKismetMathLibrary::RInterpTo(this->GetActorRotation(), rBoatUndockRotation,
									GetWorld()->GetDeltaSeconds(), fUndockingInterpSpeed);

	this->SetActorLocation(vUndockingInterpPosition);
	this->SetActorRotation(rUndockingInterpRotation);


	//unpossess the player, possess the boat

}

