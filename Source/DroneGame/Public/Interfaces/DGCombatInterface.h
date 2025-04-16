#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGCombatInterface.generated.h"

class UDGCombatComponent;

UINTERFACE(MinimalAPI)
class UDGCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class DRONEGAME_API IDGCombatInterface
{
	GENERATED_BODY()

public:
	virtual UDGCombatComponent* GetCombatComponent() const = 0;
};
