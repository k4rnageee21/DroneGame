#pragma once

#include "CoreMinimal.h"
#include "Components/DGPawnExtensionComponentBase.h"
#include "DGCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedSignature, int32, NewAmmo);

class ADGProjectileBase;
class UDGObjectPoolSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UDGCombatComponent : public UDGPawnExtensionComponentBase
{
	GENERATED_BODY()

public:	
	UDGCombatComponent();

	virtual void Shoot(const FVector& Target);

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChangedSignature OnAmmoChanged;

	void AddAmmo(int32 AddedAmmo);
	FORCEINLINE int32 GetAmmo() const { return CurrentAmmo; }

protected:
	virtual void BeginPlay() override;

	virtual void Init();
	virtual bool CanShoot(const FVector& Target) const;
	virtual FVector GetShootStartLocationFromOwner() const;
	// Don't want to make this function public
	void SetAmmo(int32 NewAmmo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0"))
	int32 StartAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (ClampMin = "0"))
	int32 MaxAmmo = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	int32 CurrentAmmo{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<ADGProjectileBase> ProjectileClass;

	UPROPERTY()
	TObjectPtr<UDGObjectPoolSubsystem> ObjectPoolSubsystem;
};
