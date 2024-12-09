#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaBarWidget.generated.h"

UCLASS()
class LOCALTESTING_API UStaminaBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Function to update the stamina bar
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateStaminaBar(float Stamina, float MaxStamina);

    // Function to set the stamina bar color
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetStaminaBarColor(FLinearColor Color);

    // Function to set the stamina text visibility
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetStaminaTextVisibility(bool bIsVisible);

protected:
    // Native implementation of the stamina bar update
    virtual void NativeUpdateStaminaBar(float Stamina, float MaxStamina);

    // Stamina bar progress bar
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaProgressBar;

    // Stamina text block
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* StaminaText;

    // Stamina bar color
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FLinearColor StaminaBarColor;

    // Stamina text visibility
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    bool bStaminaTextVisible;
};
