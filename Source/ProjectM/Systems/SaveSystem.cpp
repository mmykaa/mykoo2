// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/SaveSystem.h"

USaveSystem::USaveSystem()
{

}

void USaveSystem::Save()
{
	USaveSystem* SaveInstance = Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));

	//PlayerPosition = Player->GetActorLocation();

	UGameplayStatics::SaveGameToSlot(SaveInstance, TEXT("DefaultSaveSlot"), 0);
}

void USaveSystem::Load()
{
	USaveSystem* SaveInstance = Cast<USaveSystem>(UGameplayStatics::CreateSaveGameObject(USaveSystem::StaticClass()));
	SaveInstance = Cast<USaveSystem>(UGameplayStatics::LoadGameFromSlot("DefaultSaveSlot", 0));

	//Player->SetActorLocation(PlayerPosition);
}
