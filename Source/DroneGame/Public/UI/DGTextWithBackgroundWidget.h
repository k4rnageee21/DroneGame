#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DGTextWithBackgroundWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS(Abstract)
class DRONEGAME_API UDGTextWithBackgroundWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetText(FText InText);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextLabel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage;
};
