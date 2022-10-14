// Fill out your copyright notice in the Description page of Project Settings.


#include "UniquesHelper.h"

// Sets default values
AUniquesHelper::AUniquesHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUniquesHelper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUniquesHelper::Tick(float DeltaTime)
{
	
}

void FindUniqueActorInWorld(UObject* inActor, TSubclassOf<AActor> inActorClass, TSubclassOf<AActor> inUniqueActor)
{
	UGameplayStatics::GetActorOfClass(inActor, inActorClass);

	if (inUniqueActor != nullptr)
	{
	}
}

