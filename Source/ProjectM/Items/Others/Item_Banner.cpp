// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Banner.h"


void UItem_Banner::Item_Use()
{
	Super::Item_Use();
	UseBanner();
}

void UItem_Banner::UseBanner()
{
	switch (eBannerType)
	{
	case EBannerType::Damage:
		
			ApplyDamageBanner();
			break;
		
		case EBannerType::Defence:
		
			ApplyDefenceBanner();
			break;
		
		case EBannerType::Health:
		
			ApplyHealthBanner();
			break;
		
	}
}

void UItem_Banner::ApplyDamageBanner()
{
	// increase stats
}

void UItem_Banner::ApplyDefenceBanner()
{
	//increase stats
}

void UItem_Banner::ApplyHealthBanner()
{
	//increase stats

}
