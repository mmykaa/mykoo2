// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include <Components/BoxComponent.h>
#include "../Controllers/PlayerBehaviour.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnComponentBeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnComponentEndOverlap);
	SetRootComponent(TriggerVolume);
	RootComponent = TriggerVolume;

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyStaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractableActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayerBehaviour>(OtherActor))
	{
		OnPlayerOverlapBegin(OtherActor);
	}
}


void AInteractableActor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerBehaviour>(OtherActor))
	{
		OnPlayerOverlapEnd(OtherActor);
	}
}

void AInteractableActor::OnPlayerOverlapBegin(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("PARENT OVERLAP BEGIN"));

}

void AInteractableActor::OnPlayerOverlapEnd(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("PARENT OVERLAP END"));

}

void AInteractableActor::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("PARENT Interact"));
}
