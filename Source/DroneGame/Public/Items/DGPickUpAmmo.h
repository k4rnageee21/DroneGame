#pragma once

#include "CoreMinimal.h"
#include "Items/DGPickUpItemBase.h"
#include "DGPickUpAmmo.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ADGPickUpAmmo : public ADGPickUpItemBase
{
	GENERATED_BODY()
	
public:
	virtual void PickUp(APawn* PickingPawn) override;
};
