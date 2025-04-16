#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DGHUD.generated.h"

class UDGCrosshairWidget;
class UDGStatsWidget;

UCLASS(Abstract)
class DRONEGAME_API ADGHUD : public AHUD
{
	GENERATED_BODY()

public:
	/*	Start Widgets			*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	TObjectPtr<UDGCrosshairWidget> CrosshairWidget;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Stats Widget")
	TObjectPtr<UDGStatsWidget> StatsWidget;
	/*	End Widgets				*/
	
protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	virtual void Init();

	/*	Start Crosshair Widget	*/
	void CreateCrosshairWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	TSubclassOf<UDGCrosshairWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair Widget")
	int32 CrosshairWidgetOrderZ = 0;
	/*	End Crosshair Widget	*/

	/*	Start Stats Widget		*/
	void CreateStatsWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats Widget")
	TSubclassOf<UDGStatsWidget> StatsWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats Widget")
	int32 StatsWidgetOrderZ = 0;
	/*	End Stats Widget		*/
};
