#pragma once

#include "CoreMinimal.h"
#include "Pawns/DGPawnBase.h"
#include "DGTurret.generated.h"

class UDGTurretCombatComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGTurret : public ADGPawnBase
{
	GENERATED_BODY()

public:
	ADGTurret();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDGTurretCombatComponent> CombatComponent;
};
