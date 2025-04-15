#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UDGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDGHealthComponent();

protected:
	virtual void BeginPlay() override;	
};
