#include "Components/DGDroneCombatComponent.h"
#include "PlayerControllers/DGPlayerController.h"

bool UDGDroneCombatComponent::CanShoot(const FVector& Target) const
{
	if (!Super::CanShoot(Target))
	{
		return false;
	}

	APawn* OwningPawn = GetOwningPawn();
	if (!IsValid(OwningPawn))
	{
		return false;
	}

	const FVector DroneUpVector = OwningPawn->GetActorUpVector();
	const FVector ToTargetVector = (Target - OwningPawn->GetActorLocation()).GetSafeNormal();

	float Dot = FVector::DotProduct(ToTargetVector, -DroneUpVector);
	float AngleDegrees = FMath::Acos(Dot) * (180.f / PI);

	// DroneShootingAngle expected to be less than or equal to 90 degrees
	// (drone can shoot targets only below itself)
	return AngleDegrees < DroneShootingAngle;
}

FVector UDGDroneCombatComponent::GetHitLocationFromController() const
{
	ADGPlayerController* DronePC = GetOwningController<ADGPlayerController>();
	return IsValid(DronePC) ? DronePC->GetHitLocationUnderCrosshair() : FVector{};
}
