#pragma once

#include "CoreMinimal.h"
#include "Components/DGCombatComponent.h"
#include "DGDroneCombatComponent.generated.h"

UCLASS()
class DRONEGAME_API UDGDroneCombatComponent : public UDGCombatComponent
{
	GENERATED_BODY()

public:
	FVector GetHitLocationFromController() const;
	
protected:
	virtual bool CanShoot(const FVector& Target) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0", ClampMax = "90"))
	float DroneShootingAngle = 90.f;
};
