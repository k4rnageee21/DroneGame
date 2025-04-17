#pragma once

#include "CoreMinimal.h"
#include "Components/DGCombatComponent.h"
#include "DGTurretCombatComponent.generated.h"

UCLASS()
class DRONEGAME_API UDGTurretCombatComponent : public UDGCombatComponent
{
	GENERATED_BODY()

public:
	virtual void Shoot(const FVector& Target) override;
	
protected:
	virtual bool CanShoot(const FVector& Target) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bInfiniteAmmo = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0", ClampMax = "1"))
	float MissProbability = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float MissDistance = 100.f;
};
