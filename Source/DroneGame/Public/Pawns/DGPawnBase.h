#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGPawnBase.generated.h"

class UBoxComponent;
class UDGHealthComponent;
class UDGCombatComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGPawnBase : public APawn
{
	GENERATED_BODY()

public:
	ADGPawnBase();

protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDGHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDGCombatComponent> CombatComponent;
};
