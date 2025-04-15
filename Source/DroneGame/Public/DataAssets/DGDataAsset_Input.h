#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DGDataAsset_Input.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class DRONEGAME_API UDGDataAsset_Input : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> ShootAction;
};
