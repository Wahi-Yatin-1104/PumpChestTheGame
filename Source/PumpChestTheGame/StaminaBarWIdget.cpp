#include "StaminaBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStaminaBarWidget::NativeUpdateStaminaBar(float Stamina, float MaxStamina)
{
    if (StaminaProgressBar)
    {
        float StaminaPercentage = Stamina / MaxStamina;
        StaminaProgressBar->SetPercent(StaminaPercentage);

        // Change the color of the stamina bar based on the stamina percentage
        if (StaminaPercentage > 0.5f)
        {
            StaminaBarColor = FLinearColor::Blue;
        }
        else if (StaminaPercentage > 0.25f)
        {
            StaminaBarColor = FLinearColor::Yellow;
        }
        else
        {
            StaminaBarColor = FLinearColor::Red;
        }
        StaminaProgressBar->SetFillColorAndOpacity(StaminaBarColor);
    }

    if (StaminaText)
    {
        StaminaText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), FMath::RoundToInt(Stamina), FMath::RoundToInt(MaxStamina))));
        StaminaText->SetVisibility(bStaminaTextVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void UStaminaBarWidget::SetStaminaBarColor(FLinearColor Color)
{
    StaminaBarColor = Color;
    if (StaminaProgressBar)
    {
        StaminaProgressBar->SetFillColorAndOpacity(StaminaBarColor);
    }
}

void UStaminaBarWidget::SetStaminaTextVisibility(bool bIsVisible)
{
    bStaminaTextVisible = bIsVisible;
    if (StaminaText)
    {
        StaminaText->SetVisibility(bStaminaTextVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}
