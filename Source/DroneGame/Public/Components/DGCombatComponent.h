#pragma once

#include "CoreMinimal.h"
#include "Components/DGPawnExtensionComponentBase.h"
#include "DGCombatComponent.generated.h"

class ADGProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UDGCombatComponent : public UDGPawnExtensionComponentBase
{
	GENERATED_BODY()

public:	
	UDGCombatComponent();

	virtual void Shoot(const FVector& Start, const FVector& Target);

protected:
	virtual void BeginPlay() override;

	virtual void Init();
	virtual bool CanShoot(const FVector& Target) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0"))
	int32 StartAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0"))
	int32 MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADGProjectileBase> ProjectileClass;
};
