#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "WeatherSystem.generated.h"

// Enum for different weather types in the game
UENUM(BlueprintType)
enum class PumpGameWeather : uint8
{
    Sunny UMETA(DisplayName = "Sunny"),
    Rainy UMETA(DisplayName = "Rainy"),
    Stormy UMETA(DisplayName = "Stormy"),
    Cloudy UMETA(DisplayName = "Cloudy")
};

// Main class for handling the weather system
UCLASS()
class PUMP_CHEST_PUMP_API PumpGameWeatherClass : public AActor
{
    GENERATED_BODY()

public:
    // Constructor and Tick function
    PumpGameWeatherClass();
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // Variables for managing time in the game
    UPROPERTY(EditAnywhere, Category = "Daylight")
    float TimeOfDay; // Tracks the current time in the game world

    UPROPERTY(EditAnywhere, Category = "Daylight")
    float SpeedOfTime; // Controls how quickly time passes

    // References to lighting components
    UPROPERTY(EditAnywhere, Category = "Lighting")
    ADirectionalLight* Sunlight; // The main light source (like the sun)

    UPROPERTY(EditAnywhere, Category = "Lighting")
    ASkyLight* Skylight; // Ambient lighting for the sky

    // Weather-related properties
    UPROPERTY(EditAnywhere, Category = "Weather")
    PumpGameWeather CurrentClimateOfGame; // Current weather type in the game

    UPROPERTY(EditAnywhere, Category = "Weather")
    UParticleSystemComponent* Rain; // Particle system for rain effects

    UPROPERTY(EditAnywhere, Category = "Weather")
    UParticleSystemComponent* Lightning; // Particle system for lightning effects

    UPROPERTY(EditAnywhere, Category = "Weather")
    float SpeedOfWind; // Speed of the wind in the game

    UPROPERTY(EditAnywhere, Category = "Weather")
    FLinearColor ColorOfFog; // Color of the fog in the game

    UPROPERTY(EditAnywhere, Category = "Weather")
    float DensityOfFog; // Controls how thick the fog is

    // Sound effects for weather
    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* SoundOfRain; // Sound cue for rain

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* SoundOfThunder; // Sound cue for thunder

    UPROPERTY()
    UAudioComponent* GameWeatherAudio; // Audio component to play weather sounds

    // Temperature and seasonal information
    UPROPERTY(EditAnywhere, Category = "Temperature")
    float GameCurrentTemperature; // Current temperature in the game

    UPROPERTY(EditAnywhere, Category = "Season")
    FString GameCurrentSeason; // Current season (e.g., Winter, Spring)

    // Internal flag to track weather transitions
    bool GameWeatherSwitching; // Indicates if a weather transition is happening

    // Private helper functions for managing weather
    void ChangeSun(float TimeChange); // Adjusts sunlight based on time of day
    void ChangeWeather(float TimeChange); // Updates weather based on elapsed time
    void ChangeFog(); // Adjusts fog density and color
    void ChangeWind(); // Updates wind speed
    void MakeThunder(); // Triggers thunder effects
    void ChangeWeather(PumpGameWeather ChangedWeather); // Sets a new weather type
    void BeginWeatherChange(PumpGameWeather ChangedWeather); // Starts a weather transition
    void EndWeatherChange(); // Ends a weather transition
};
