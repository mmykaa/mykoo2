// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */



UCLASS(Blueprintable)
class PROJECTM_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	FString ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) UStaticMeshComponent* ItemMesh;
};