#include "HUDs/DGHUD.h"
#include "UI/DGCrosshairWidget.h"
#include "UI/DGStatsWidget.h"

void ADGHUD::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void ADGHUD::Init()
{
	CreateCrosshairWidget();
	CreateStatsWidget();
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

void ADGHUD::CreateStatsWidget()
{
	if (!StatsWidgetClass)
	{
		return;
	}

	StatsWidget = CreateWidget<UDGStatsWidget>(GetOwningPlayerController(), StatsWidgetClass);
	if (IsValid(StatsWidget))
	{
		StatsWidget->AddToViewport(StatsWidgetOrderZ);
	}
}
