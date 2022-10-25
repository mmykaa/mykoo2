// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Engine/StaticMesh.h>
#include "Item.generated.h"

/**
 * 
 */



//UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
UCLASS(BlueprintType)
class PROJECTM_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	FString ItemName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	FString ItemDescription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UTexture2D* ItemIcon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	TSubclassOf<AActor> ItemActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)	UStaticMesh* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bCanItemStack;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int iItemAmount;

	bool GetCanStack() { return bCanItemStack; }
	int GetAmountItemAmount() { return iItemAmount; }
	void AddAmount(int &inAmount) { iItemAmount += inAmount; }

	UFUNCTION() virtual void Item_Use();

	UFUNCTION(BlueprintImplementableEvent) void Item_OnUse();
};
