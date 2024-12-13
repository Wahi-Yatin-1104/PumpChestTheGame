// Written by Yatin Wahi

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicLightingSystem.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API ADynamicLightingSystem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADynamicLightingSystem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to apply intense mode lighting
    UFUNCTION(BlueprintCallable, Category = "Lighting")
    void ApplyIntenseModeLighting();

    // Function to remove intense mode lighting
    UFUNCTION(BlueprintCallable, Category = "Lighting")
    void RemoveIntenseModeLighting();

    // Function to check and update lighting based on stamina
    UFUNCTION(BlueprintCallable, Category = "Lighting")
    void UpdateLighting(float Stamina);

private:
    // Post-process component for red tint effect
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPostProcessComponent* PostProcessComponent;

    // Flag to track if intense mode is active
    bool bIsIntenseModeActive;

    // Helper function to initialize post-process settings
    void InitializePostProcessSettings();

    // Timer to gradually fade out the red tint
    FTimerHandle FadeOutTimerHandle;

    // Function to gradually remove the red tint
    void GraduallyRemoveRedTint();
};