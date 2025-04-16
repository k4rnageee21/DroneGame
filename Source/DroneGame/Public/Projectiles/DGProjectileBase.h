#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGProjectileBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADGProjectileBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnLifetimeEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0"))
	float BaseDamage = 25.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "1"))
	float LifetimeDuration = 5.f;

	FTimerHandle LifetimeTH; // TODO: Remove this if I wouldn't be able to make object pool in time
};
