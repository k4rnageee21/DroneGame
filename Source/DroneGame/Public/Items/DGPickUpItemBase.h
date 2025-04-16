#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DGPickupItemInterface.h"
#include "DGPickUpItemBase.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGPickUpItemBase : public AActor, public IDGPickupItemInterface
{
	GENERATED_BODY()
	
public:	
	ADGPickUpItemBase();

	virtual void PickUp(APawn* PickingPawn) override;

protected:
	virtual float CalculateAddedValue();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0"))
	float MinValue = 5.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0"))
	float MaxValue = 20.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0"))
	float FixedValue = 10.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bShouldAddFixedValue = false;
};
