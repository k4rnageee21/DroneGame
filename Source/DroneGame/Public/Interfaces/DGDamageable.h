#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGDamageable.generated.h"

class UDGHealthComponent;

UINTERFACE(MinimalAPI)
class UDGDamageable : public UInterface
{
	GENERATED_BODY()
};

class DRONEGAME_API IDGDamageable
{
	GENERATED_BODY()

public:
	virtual UDGHealthComponent* GetHealthComponent() const = 0;
};
