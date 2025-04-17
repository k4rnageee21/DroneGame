#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGPoolable.generated.h"

UINTERFACE(MinimalAPI)
class UDGPoolable : public UInterface
{
	GENERATED_BODY()
};

class DRONEGAME_API IDGPoolable
{
	GENERATED_BODY()

public:
	virtual void OnGetFromPool() = 0;
	virtual void OnReturnToPool() = 0;
};
