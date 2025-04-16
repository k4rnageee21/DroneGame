#include "UI/DGTextWithBackgroundWidget.h"
#include "Components/TextBlock.h"

void UDGTextWithBackgroundWidget::SetText(FText InText)
{
	if (IsValid(TextLabel))
	{
		TextLabel->SetText(InText);
	}
}
