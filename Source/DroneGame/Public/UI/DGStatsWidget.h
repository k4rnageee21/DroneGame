#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGStatsWidget.generated.h"

class UDGTextWithBackgroundWidget;

UCLASS(Abstract)
class DRONEGAME_API UDGStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetAmmo(int32 Ammo);

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Health);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDGTextWithBackgroundWidget> TurretsLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDGTextWithBackgroundWidget> HealthLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDGTextWithBackgroundWidget> AmmoLabel;
};
