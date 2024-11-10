#include "GameWeatherClass.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"

// Constructor: Initializes variables and sets default values
PumpGameWeatherClass::PumpGameWeatherClass()
{
    PrimaryActorTick.bCanEverTick = true; // Allow ticking for real-time updates

    // Setting up default values (feels like setting up a new day)
    TimeOfDay = 6.0f;               // Start at 6 AM
    SpeedOfTime = 60.0f;            // One in-game hour passes in 1 real-world minute
    CurrentClimateOfGame = PumpGameWeather::Sunny; // Default weather is sunny
    SpeedOfWind = 0.0f;             // No wind at the start
    DensityOfFog = 0.01f;           // Barely any fog initially
    GameCurrentTemperature = 20.0f; // Comfortable temperature
    GameCurrentSeason = "Spring";  // Why not start with spring?
    GameWeatherSwitching = false;  // Not switching weather by default

    // Create particle systems for rain and lightning, attach to root
    Rain = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Rain"));
    Rain->SetupAttachment(RootComponent);
    Rain->SetAutoActivate(false); // Rain doesn't start until it needs to

    Lightning = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lightning"));
    Lightning->SetupAttachment(RootComponent);
    Lightning->SetAutoActivate(false); // Same for lightning
}

// Runs once when the game begins
void PumpGameWeatherClass::BeginPlay()
{
    Super::BeginPlay();

    // Look for a directional light (the "sun") in the scene
    TArray<AActor*> DirectionalLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), DirectionalLights);
    if (DirectionalLights.Num() > 0)
    {
        Sunlight = Cast<ADirectionalLight>(DirectionalLights[0]); // Assume the first one is the sun
    }

    // Look for a skylight
    TArray<AActor*> SkyLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyLight::StaticClass(), SkyLights);
    if (SkyLights.Num() > 0)
    {
        Skylight = Cast<ASkyLight>(SkyLights[0]);
    }

    // Set up audio for rain, but keep it off for now
    if (SoundOfRain)
    {
        GameWeatherAudio = UGameplayStatics::SpawnSound2D(this, SoundOfRain);
        GameWeatherAudio->Stop(); // Wait until it actually rains
    }
}

// Called every frame
void PumpGameWeatherClass::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Increment time of day, loop back at midnight
    TimeOfDay += DeltaTime * (SpeedOfTime / 3600.0f); // Convert speed to hours per second
    if (TimeOfDay >= 24.0f) TimeOfDay = 0.0f;

    // Update sun, weather, fog, and wind each frame
    ChangeSun(DeltaTime);
    ChnageWeather(DeltaTime);
    ChangeFog();
    ChangeWind();

    // Occasionally trigger thunder during storms
    if (CurrentClimateOfGame == PumpGameWeather::Stormy && FMath::RandRange(0, 100) < 1) // 1% chance
    {
        Lightning->ActivateSystem();
        MakeThunder();
    }
}

// Updates sun's position based on time of day
void PumpGameWeatherClass::ChangeSun(float TimeChange)
{
    if (Sunlight)
    {
        float SunRotation = (TimeOfDay / 24.0f) * 360.0f - 90.0f; // Calculate rotation
        Sunlight->SetActorRotation(FRotator(SunRotation, 0.0f, 0.0f));
    }
}

// Handles random weather changes
void PumpGameWeatherClass::ChnageWeather(float TimeChange)
{
    if (!GameWeatherSwitching)
    {
        // Random chance to change the weather
        if (FMath::RandRange(0, 1000) < 1) // Super rare chance (0.1%)
        {
            PumpGameWeather NewWeather = static_cast<PumpGameWeather>(FMath::RandRange(0, 3));
            ChangeWeather(NewWeather);
        }
    }
}

// Adjust fog properties based on current weather
void PumpGameWeatherClass::ChangeFog()
{
    if (CurrentClimateOfGame == PumpGameWeather::Rainy || CurrentClimateOfGame == PumpGameWeather::Stormy)
    {
        DensityOfFog = 0.1f;         // Thick fog for bad weather
        ColorOfFog = FLinearColor::Gray; // Gloomy tones
    }
    else
    {
        DensityOfFog = 0.01f;        // Thin fog for clear skies
        ColorOfFog = FLinearColor::Blue; // Bright and sunny
    }
}

// Updates wind speed dynamically
void PumpGameWeatherClass::ChangeWind()
{
    SpeedOfWind = CurrentClimateOfGame == PumpGameWeather::Sunny ? 0.1f : FMath::RandRange(0.5f, 2.0f);
}

// Plays a thunder sound effect
void PumpGameWeatherClass::MakeThunder()
{
    if (SoundOfThunder)
    {
        UGameplayStatics::PlaySound2D(this, SoundOfThunder);
    }
}

// Initiates a weather change
void PumpGameWeatherClass::ChangeWeather(PumpGameWeather NewWeather)
{
    if (CurrentClimateOfGame != NewWeather)
    {
        BeginWeatherChange(NewWeather);
    }
}

// Begins the weather change process
void PumpGameWeatherClass::BeginWeatherChange(PumpGameWeather NewWeather)
{
    GameWeatherSwitching = true;

    CurrentClimateOfGame = NewWeather; // Update the current weather

    // Activate or deactivate rain and audio
    if (NewWeather == PumpGameWeather::Rainy || NewWeather == PumpGameWeather::Stormy)
    {
        Rain->Activate();
        if (GameWeatherAudio) GameWeatherAudio->Play();
    }
    else
    {
        Rain->Deactivate();
        if (GameWeatherAudio) GameWeatherAudio->Stop();
    }

    GameWeatherSwitching = false; // Done with the switch
}

// Optional end-weather-change method (not used here but can be handy)
void PumpGameWeatherClass::EndWeatherChange()
{
    GameWeatherSwitching = false;
}
