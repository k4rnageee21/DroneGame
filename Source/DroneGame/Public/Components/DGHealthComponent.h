#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UDGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDGHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDeadSignature OnDead;

	FORCEINLINE float GetHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	bool IsDead() const;
	void Heal(float HealAmount);
	void TakeDamage(float DamageAmount);

protected:
	virtual void BeginPlay() override;

private:
	void Init();

	// Don't want to make it public
	void SetHealth(float NewHealth);
	void CheckIfDead();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Health", meta = (ClampMin = "0"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Health")
	float CurrentHealth{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Health", meta = (ClampMin = "0"))
	float ZeroHealthCheckTolerace = 1e-4f;

	bool bAlreadyDead = false;
};
