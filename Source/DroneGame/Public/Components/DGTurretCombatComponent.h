#pragma once

#include "CoreMinimal.h"
#include "Components/DGCombatComponent.h"
#include "DGTurretCombatComponent.generated.h"

UCLASS()
class DRONEGAME_API UDGTurretCombatComponent : public UDGCombatComponent
{
	GENERATED_BODY()
	
protected:
	virtual bool CanShoot(const FVector& Target) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bInfiniteAmmo = true;
};
