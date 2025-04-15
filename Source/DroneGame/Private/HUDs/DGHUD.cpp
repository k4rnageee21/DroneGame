#include "HUDs/DGHUD.h"
#include "UI/DGCrosshairWidget.h"

void ADGHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateCrosshairWidget();
}

void ADGHUD::CreateCrosshairWidget()
{
	if (!CrosshairWidgetClass)
	{
		return;
	}

	CrosshairWidget = CreateWidget<UDGCrosshairWidget>(GetOwningPlayerController(), CrosshairWidgetClass);
	if (IsValid(CrosshairWidget))
	{
		CrosshairWidget->AddToViewport(CrosshairWidgetOrderZ);
	}
}
