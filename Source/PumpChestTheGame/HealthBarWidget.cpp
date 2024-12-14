#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::NativeUpdateHealthBar(float Health, float MaxHealth)
{
    if (HealthProgressBar)
    {
        float HealthPercentage = Health / MaxHealth;
        HealthProgressBar->SetPercent(HealthPercentage);

        // Change the color of the health bar based on the health percentage
        if (HealthPercentage > 0.5f)
        {
            HealthBarColor = FLinearColor::Green;
        }
        else if (HealthPercentage > 0.25f)
        {
            HealthBarColor = FLinearColor::Yellow;
        }
        else
        {
            HealthBarColor = FLinearColor::Red;
        }
        HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
    }

    if (HealthText)
    {
        HealthText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), FMath::RoundToInt(Health), FMath::RoundToInt(MaxHealth))));
        HealthText->SetVisibility(bHealthTextVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}

void UHealthBarWidget::SetHealthBarColor(FLinearColor Color)
{
    HealthBarColor = Color;
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
    }
}

void UHealthBarWidget::SetHealthTextVisibility(bool bIsVisible)
{
    bHealthTextVisible = bIsVisible;
    if (HealthText)
    {
        HealthText->SetVisibility(bHealthTextVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}
