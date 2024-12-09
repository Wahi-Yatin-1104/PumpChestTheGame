#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class LOCALTESTING_API AMyHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyHUD();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Function to update the health bar
    void UpdateHealthBar(float Health, float MaxHealth);

    // Function to update the stamina bar
    void UpdateStaminaBar(float Stamina, float MaxStamina);

private:
    // Health bar widget class
    TSubclassOf<class UHealthBarWidget> HealthBarWidgetClass;

    // Stamina bar widget class
    TSubclassOf<class UStaminaBarWidget> StaminaBarWidgetClass;

    // Health bar widget instance
    UHealthBarWidget* HealthBarWidget;

    // Stamina bar widget instance
    UStaminaBarWidget* StaminaBarWidget;
};
