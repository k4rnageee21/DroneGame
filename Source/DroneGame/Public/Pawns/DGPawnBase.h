#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/DGDamageable.h"
#include "DGPawnBase.generated.h"

class UBoxComponent;
class UDGHealthComponent;
class UDGCombatComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGPawnBase : public APawn, public IDGDamageable
{
	GENERATED_BODY()

public:
	ADGPawnBase();

	virtual UDGHealthComponent* GetHealthComponent() const override { return HealthComponent; }

protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDGHealthComponent> HealthComponent;
};
