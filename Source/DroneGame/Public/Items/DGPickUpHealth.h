#pragma once

#include "CoreMinimal.h"
#include "Items/DGPickUpItemBase.h"
#include "DGPickUpHealth.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ADGPickUpHealth : public ADGPickUpItemBase
{
	GENERATED_BODY()

public:
	virtual void PickUp(APawn* PickingPawn) override;
};
