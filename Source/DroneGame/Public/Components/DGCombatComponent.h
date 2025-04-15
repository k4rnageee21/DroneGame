#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGCombatComponent.generated.h"

class ADGProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UDGCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDGCombatComponent();

	void Shoot(const FVector& Start, const FVector& LookAtVector);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Combat")
	TSubclassOf<ADGProjectileBase> ProjectileClass;
};
