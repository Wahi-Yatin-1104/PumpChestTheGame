#include "DayNightCycle.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Components/DirectionalLightComponent.h"

ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;

    CurrentTime = 12.0f; // Start at noon
    TimeScale = 1.0f;    // Real-time
    DayLength = 24.0f;   // 24 hour day
}

void ADayNightCycle::BeginPlay()
{
    Super::BeginPlay();

    // Find the directional light in the level
    for (TActorIterator<ADirectionalLight> It(GetWorld()); It; ++It)
    {
        SunLight = *It;
        break;  // Take the first directional light we find
    }

    // If we didn't find a light, log a warning
    if (!SunLight)
    {
        UE_LOG(LogTemp, Warning, TEXT("DayNightCycle: No DirectionalLight found in the level"));
    }
}

void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Calculate time progression
    float TimeChangeThisFrame = (DeltaTime / DayLength) * TimeScale;
    CurrentTime += TimeChangeThisFrame;

    // Wrap time between 0 and 24
    if (CurrentTime >= 24.0f)
    {
        CurrentTime -= 24.0f;
    }

    UpdateSunPosition();
}

void ADayNightCycle::UpdateSunPosition()
{
    if (!SunLight)
    {
        return;
    }

    // Convert time of day to rotation (360 degrees = 24 hours)
    float SunRotation = (CurrentTime / 24.0f) * 360.0f - 90.0f;
    
    // Update sun rotation
    FRotator NewRotation = FRotator(SunRotation, 0.0f, 0.0f);
    SunLight->SetActorRotation(NewRotation);

    // Get the light component and adjust intensity
    UDirectionalLightComponent* LightComponent = Cast<UDirectionalLightComponent>(SunLight->GetLightComponent());
    if (LightComponent)
    {
        float Intensity = FMath::Sin((CurrentTime / 24.0f) * PI);
        Intensity = FMath::Max(0.0f, Intensity);  // Keep intensity non-negative
        LightComponent->SetIntensity(Intensity * 10.0f);  // Scale to reasonable values
    }
}