#include "Components/DGTurretCombatComponent.h"

bool UDGTurretCombatComponent::CanShoot(const FVector& Target) const
{
	return bInfiniteAmmo ? true : Super::CanShoot(Target);
}
