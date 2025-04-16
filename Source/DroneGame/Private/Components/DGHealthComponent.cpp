#include "Components/DGHealthComponent.h"

UDGHealthComponent::UDGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UDGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UDGHealthComponent::Init()
{
	CurrentHealth = MaxHealth;
	bAlreadyDead = false;
}

bool UDGHealthComponent::IsDead() const
{
	return bAlreadyDead;
}

void UDGHealthComponent::SetHealth(float NewHealth)
{
	if (!IsDead())
	{
		CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
		OnHealthChanged.Broadcast(CurrentHealth);
		CheckIfDead();
	}
}

void UDGHealthComponent::CheckIfDead()
{
	if (!bAlreadyDead && FMath::IsNearlyZero(CurrentHealth, ZeroHealthCheckTolerace))
	{
		bAlreadyDead = true;
		OnDead.Broadcast();
	}
}

void UDGHealthComponent::Heal(float HealAmount)
{
	if (!IsDead())
	{
		float MaxHealAmount = MaxHealth - CurrentHealth;
		HealAmount = FMath::Clamp(HealAmount, 0.f, MaxHealAmount);
		SetHealth(CurrentHealth + HealAmount);
	}
}

void UDGHealthComponent::TakeDamage(float DamageAmount)
{
	if (!IsDead())
	{
		DamageAmount = FMath::Clamp(DamageAmount, 0.f, CurrentHealth);
		SetHealth(CurrentHealth - DamageAmount);
	}
}
