// Written by Yatin Wahi

#include "DynamicLightingSystem.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ADynamicLightingSystem::ADynamicLightingSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize the PostProcessComponent
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
    PostProcessComponent->SetupAttachment(RootComponent);

    bIsIntenseModeActive = false;
    InitializePostProcessSettings();
}

// Called when the game starts or when spawned
void ADynamicLightingSystem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ADynamicLightingSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Initialize post-process settings for red tint effect
void ADynamicLightingSystem::InitializePostProcessSettings()
{
    if (PostProcessComponent)
    {
        PostProcessComponent->Settings.bOverride_ColorSaturation = true;
        PostProcessComponent->Settings.bOverride_SceneFringeIntensity = true;
        PostProcessComponent->Settings.bOverride_ColorGradingIntensity = true;
        PostProcessComponent->Settings.ColorGradingIntensity = 0.0f;
        PostProcessComponent->Settings.SceneFringeIntensity = 0.0f;
    }
}

// Apply intense mode lighting with a red tint
void ADynamicLightingSystem::ApplyIntenseModeLighting()
{
    if (bIsIntenseModeActive)
    {
        return;
    }

    if (PostProcessComponent)
    {
        PostProcessComponent->Settings.ColorSaturation = FVector4(1.0f, 0.2f, 0.2f, 1.0f);
        PostProcessComponent->Settings.ColorGradingIntensity = 0.5f;
        PostProcessComponent->Settings.SceneFringeIntensity = 1.0f;
        UE_LOG(LogTemp, Log, TEXT("Intense mode lighting applied."));
    }

    bIsIntenseModeActive = true;
}

// Remove intense mode lighting
void ADynamicLightingSystem::RemoveIntenseModeLighting()
{
    if (!bIsIntenseModeActive)
    {
        return;
    }

    if (PostProcessComponent)
    {
        PostProcessComponent->Settings.ColorSaturation = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
        PostProcessComponent->Settings.ColorGradingIntensity = 0.0f;
        PostProcessComponent->Settings.SceneFringeIntensity = 0.0f;
        UE_LOG(LogTemp, Log, TEXT("Intense mode lighting removed."));
    }

    bIsIntenseModeActive = false;
}

// Update lighting based on stamina
void ADynamicLightingSystem::UpdateLighting(float Stamina)
{
    if (Stamina <= 10.0f && !bIsIntenseModeActive)
    {
        ApplyIntenseModeLighting();
    }
    else if (Stamina > 10.0f && bIsIntenseModeActive)
    {
        GetWorldTimerManager().ClearTimer(FadeOutTimerHandle);
        GetWorldTimerManager().SetTimer(FadeOutTimerHandle, this, &ADynamicLightingSystem::GraduallyRemoveRedTint, 0.1f, true);
    }
}

// Gradually remove the red tint over time
void ADynamicLightingSystem::GraduallyRemoveRedTint()
{
    if (!bIsIntenseModeActive)
    {
        GetWorldTimerManager().ClearTimer(FadeOutTimerHandle);
        return;
    }

    if (PostProcessComponent)
    {
        float CurrentIntensity = PostProcessComponent->Settings.ColorGradingIntensity;
        CurrentIntensity = FMath::Clamp(CurrentIntensity - 0.05f, 0.0f, 0.5f);
        PostProcessComponent->Settings.ColorGradingIntensity = CurrentIntensity;

        if (CurrentIntensity <= 0.0f)
        {
            RemoveIntenseModeLighting();
            GetWorldTimerManager().ClearTimer(FadeOutTimerHandle);
        }
    }
}
