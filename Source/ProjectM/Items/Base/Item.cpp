// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

void UItem::AddAmount(int inAmount)
{
	iItemAmount += inAmount;
}

void UItem::Item_Use()
{
	UE_LOG(LogTemp, Warning, TEXT("BASE ITEM USED"));
}

