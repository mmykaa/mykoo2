// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectM/Items/Base/Item.h"
#include "Item_Herb.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UItem_Herb : public UItem
{
	GENERATED_BODY()

		virtual void Item_Use() override;
};
