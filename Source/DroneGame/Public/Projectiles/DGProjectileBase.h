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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UBoxComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;
};
