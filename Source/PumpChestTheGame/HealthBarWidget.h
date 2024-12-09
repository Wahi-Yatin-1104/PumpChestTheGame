#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class LOCALTESTING_API UHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Function to update the health bar
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateHealthBar(float Health, float MaxHealth);

    // Function to set the health bar color
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetHealthBarColor(FLinearColor Color);

    // Function to set the health text visibility
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetHealthTextVisibility(bool bIsVisible);

protected:
    // Native implementation of the health bar update
    virtual void NativeUpdateHealthBar(float Health, float MaxHealth);

    // Health bar progress bar
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;

    // Health text block
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HealthText;

    // Health bar color
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FLinearColor HealthBarColor;

    // Health text visibility
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    bool bHealthTextVisible;
};
