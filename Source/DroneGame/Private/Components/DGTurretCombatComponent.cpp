#include "Components/DGTurretCombatComponent.h"

void UDGTurretCombatComponent::Shoot(const FVector& Target)
{
	FVector ModifiedTarget = Target;
    if (FMath::FRand() < MissProbability)
    {
        const FVector MissOffset = FVector(
            FMath::FRandRange(-MissDistance, MissDistance),
            FMath::FRandRange(-MissDistance, MissDistance),
            FMath::FRandRange(-MissDistance, MissDistance));

        ModifiedTarget += MissOffset;
    }

	Super::Shoot(ModifiedTarget);
}

bool UDGTurretCombatComponent::CanShoot(const FVector& Target) const
{
	return bInfiniteAmmo ? true : Super::CanShoot(Target);
}
