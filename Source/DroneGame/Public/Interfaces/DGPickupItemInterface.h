#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGPickupItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDGPickupItemInterface : public UInterface
{
	GENERATED_BODY()
};

class DRONEGAME_API IDGPickupItemInterface
{
	GENERATED_BODY()

public:
	virtual void PickUp(APawn* PickingPawn) = 0;
};
