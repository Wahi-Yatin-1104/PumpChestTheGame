#include "MyHUD.h"
#include "HealthBarWidget.h"
#include "StaminaBarWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AMyHUD::AMyHUD()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Find the widget classes
    static ConstructorHelpers::FClassFinder<UHealthBarWidget> HealthBarWidgetObj(TEXT("/Game/UI/HealthBarWidget"));
    if (HealthBarWidgetObj.Succeeded())
    {
        HealthBarWidgetClass = HealthBarWidgetObj.Class;
    }

    static ConstructorHelpers::FClassFinder<UStaminaBarWidget> StaminaBarWidgetObj(TEXT("/Game/UI/StaminaBarWidget"));
    if (StaminaBarWidgetObj.Succeeded())
    {
        StaminaBarWidgetClass = StaminaBarWidgetObj.Class;
    }
}

void AMyHUD::BeginPlay()
{
    Super::BeginPlay();

    // Create and add the health bar widget to the viewport
    if (HealthBarWidgetClass)
    {
        HealthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarWidgetClass);
        if (HealthBarWidget)
        {
            HealthBarWidget->AddToViewport(1);
            HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }

    // Create and add the stamina bar widget to the viewport
    if (StaminaBarWidgetClass)
    {
        StaminaBarWidget = CreateWidget<UStaminaBarWidget>(GetWorld(), StaminaBarWidgetClass);
        if (StaminaBarWidget)
        {
            StaminaBarWidget->AddToViewport(1);
            StaminaBarWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
}

void AMyHUD::UpdateHealthBar(float Health, float MaxHealth)
{
    if (HealthBarWidget)
    {
        HealthBarWidget->UpdateHealthBar(Health, MaxHealth);
    }
}

void AMyHUD::UpdateStaminaBar(float Stamina, float MaxStamina)
{
    if (StaminaBarWidget)
    {
        StaminaBarWidget->UpdateStaminaBar(Stamina, MaxStamina);
    }
}
