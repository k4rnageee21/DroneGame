#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGHUD.generated.h"

class UDGCrosshairWidget;

UCLASS(Abstract)
class DRONEGAME_API ADGHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	TObjectPtr<UDGCrosshairWidget> CrosshairWidget;
	
protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	/*	Start Crosshair Widget	*/
	void CreateCrosshairWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	TSubclassOf<UDGCrosshairWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	int32 CrosshairWidgetOrderZ = 0;
	/*	End Crosshair Widget	*/
};
