// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Banner.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBannerType : uint8
{
	Damage UMETA(DisplayName = "Damage"),
	Defence UMETA(DisplayName = "Defence"),
	Health UMETA(DisplayName = "Health")

	//Damage UMETA(DisplayName = "Damage"),

};

UCLASS()
class PROJECTM_API UItem_Banner : public UItem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) EBannerType eBannerType;

	void UseBanner();
	void ApplyDamageBanner();
	void ApplyDefenceBanner();
	void ApplyHealthBanner();
};
