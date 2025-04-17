#pragma once

#include "CoreMinimal.h"
#include "Pawns/DGPawnBase.h"
#include "Interfaces/DGCombatInterface.h"
#include "DGTurret.generated.h"

class UDGTurretCombatComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGTurret : public ADGPawnBase, public IDGCombatInterface
{
	GENERATED_BODY()

public:
	ADGTurret();

	virtual UDGCombatComponent* GetCombatComponent() const override;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDGTurretCombatComponent> CombatComponent;
};
