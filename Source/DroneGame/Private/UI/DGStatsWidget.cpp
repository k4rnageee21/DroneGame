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

#undef LOCTEXT_NAMESPACE
