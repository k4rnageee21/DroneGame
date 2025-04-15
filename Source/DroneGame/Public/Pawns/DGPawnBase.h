#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DGPawnBase.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class DRONEGAME_API ADGPawnBase : public APawn
{
	GENERATED_BODY()

public:
	ADGPawnBase();

	UFUNCTION(BlueprintCallable)
	virtual void Shoot(FVector Start, FVector LookAtVector);

protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/
};
