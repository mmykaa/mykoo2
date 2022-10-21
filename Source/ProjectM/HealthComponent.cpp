// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "StatsComponent.h"

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

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::TakeDamage(int inDamageAmount)
{
	if (iCurrentHealth > 0)
	{
		int m_DamageToApply = inDamageAmount - iDefence;

		if (m_DamageToApply <= 0)
		{
			return;
		}

		iCurrentHealth -= m_DamageToApply;

		if (iCurrentHealth <= 0)
		{
			iCurrentHealth = 0;
		}
	}
}

void UHealthComponent::Heal(int inHealAmount)
{
	if (iCurrentHealth < iMaxHealth)
	{
		iCurrentHealth += inHealAmount;

		if (iCurrentHealth >= iMaxHealth)
		{
			iCurrentHealth = iMaxHealth;
		}
	}
}

void UHealthComponent::IncreaseMaxHealth(int inIncreaseAmount)
{
	if (iMaxHealth > 0 && iCurrentHealth > 0)
	{
		iMaxHealth += inIncreaseAmount;

		UpdateStatsHealth();
	}
}

void UHealthComponent::DecreaseMaxHealth(int inDecreaseAmount)
{
	if (iMaxHealth > 0 && iCurrentHealth > 0)
	{
		iMaxHealth -= inDecreaseAmount;

		int m_minMaxHealth = ((iMaxHealth / 100) * 20);
		
		if (iMaxHealth -= inDecreaseAmount < m_minMaxHealth)
		{
			iMaxHealth = m_minMaxHealth;
		}

		UpdateStatsHealth();
	}
}

void UHealthComponent::GetBaseStats(UStatsComponent* inStatsComponent)
{
	StatsComponent = Cast<UStatsComponent>(inStatsComponent);
	SetBaseHealth();
}

void UHealthComponent::SetBaseHealth()
{

	iMaxHealth = StatsComponent->GetStatsHealth();
	iCurrentHealth = iMaxHealth;
	
	iDefence = StatsComponent->GetStatsDefence();
}

void UHealthComponent::UpdateStatsHealth()
{
	StatsComponent->SetStatsHealth(iMaxHealth);
}

