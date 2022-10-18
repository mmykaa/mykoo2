// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	iCurrentHealth = iMaxHealth;
	// ...
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(int DamageAmount)
{
	if (iCurrentHealth > 0)
	{
		iCurrentHealth -= DamageAmount;

		if (iCurrentHealth <= 0)
		{
			iCurrentHealth = 0;
		}
	}
}

void UHealthComponent::Heal(int HealAmount)
{
	if (iCurrentHealth < iMaxHealth)
	{
		iCurrentHealth += HealAmount;

		if (iCurrentHealth >= iMaxHealth)
		{
			iCurrentHealth = iMaxHealth;
		}
	}
}

void UHealthComponent::IncreaseMaxHealth(int IncreaseAmount)
{
	if (iMaxHealth > 0 && iCurrentHealth > 0)
	{
		iMaxHealth += IncreaseAmount;
	}
}

void UHealthComponent::DecreaseMaxHealth(int DecreaseAmount)
{
	if (iMaxHealth > 0 && iCurrentHealth > 0)
	{
		iMaxHealth -= DecreaseAmount;

		int m_minMaxHealth = ((iMaxHealth / 100) * 20);
		
		if (iMaxHealth -= DecreaseAmount < m_minMaxHealth)
		{
			iMaxHealth = m_minMaxHealth;
		}
	}
}

