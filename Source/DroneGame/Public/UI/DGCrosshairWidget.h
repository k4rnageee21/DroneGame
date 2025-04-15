#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGCrosshairWidget.generated.h"

class UImage;

UCLASS(Abstract)
class DRONEGAME_API UDGCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> CrosshairImage;
};
