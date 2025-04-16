#include "UI/DGStatsWidget.h"
#include "Components/TextBlock.h"
#include "UI/DGTextWithBackgroundWidget.h"

#define LOCTEXT_NAMESPACE "DroneGame"

void UDGStatsWidget::SetAmmo(int32 Ammo)
{
	if (IsValid(AmmoLabel))
	{
		FFormatNamedArguments Args;
		Args.Add("Ammo", Ammo);

		FText FormattedText = FText::Format(
			NSLOCTEXT("DroneGame", "AmmoLabel", "Ammo: {Ammo}"),
			Args
		);

		AmmoLabel->SetText(FormattedText);
	}
}

void UDGStatsWidget::SetHealth(float Health)
{
	if (IsValid(HealthLabel))
	{
		Health = FMath::FloorToFloat(Health);
		FFormatNamedArguments Args;
		Args.Add("Health", Health);

		FText FormattedText = FText::Format(
			NSLOCTEXT("DroneGame", "HealthLabel", "Health: {Health}"),
			Args
		);

		HealthLabel->SetText(FormattedText);
	}
}

#undef LOCTEXT_NAMESPACE
