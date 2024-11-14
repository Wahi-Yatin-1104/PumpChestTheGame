#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "WeatherSystem.generated.h"

// Forward declarations
class ADirectionalLight;
class ASkyLight;

UENUM(BlueprintType)
enum class EPumpGameWeather : uint8
{
    Sunny   UMETA(DisplayName = "Sunny"),
    Rainy   UMETA(DisplayName = "Rainy"),
    Stormy  UMETA(DisplayName = "Stormy"),
    Cloudy  UMETA(DisplayName = "Cloudy")
};

UCLASS()
class PUMPCHESTTHEGAME_API AWeatherSystem : public AActor
{
    GENERATED_BODY()

public:
    AWeatherSystem();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Daylight")
    float TimeOfDay;

    UPROPERTY(EditAnywhere, Category = "Daylight")
    float SpeedOfTime;

    UPROPERTY(EditAnywhere, Category = "Lighting")
    ADirectionalLight* Sunlight;

    UPROPERTY(EditAnywhere, Category = "Lighting")
    ASkyLight* Skylight;

    UPROPERTY(EditAnywhere, Category = "Weather")
    EPumpGameWeather CurrentClimateOfGame;

    UPROPERTY(EditAnywhere, Category = "Weather")
    UParticleSystemComponent* Rain;

    UPROPERTY(EditAnywhere, Category = "Weather")
    UParticleSystemComponent* Lightning;

    UPROPERTY(EditAnywhere, Category = "Weather")
    float SpeedOfWind;

    UPROPERTY(EditAnywhere, Category = "Weather")
    FLinearColor ColorOfFog;

    UPROPERTY(EditAnywhere, Category = "Weather")
    float DensityOfFog;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* SoundOfRain;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* SoundOfThunder;

    UPROPERTY()
    UAudioComponent* GameWeatherAudio;

    UPROPERTY(EditAnywhere, Category = "Temperature")
    float GameCurrentTemperature;

    UPROPERTY(EditAnywhere, Category = "Season")
    FString GameCurrentSeason;

    bool bGameWeatherSwitching;

    void ChangeSun(float TimeChange);
    void ChangeWeather(float TimeChange);
    void ChangeFog();
    void ChangeWind();
    void MakeThunder();
    void ChangeWeatherTo(EPumpGameWeather ChangedWeather);
    void BeginWeatherChange(EPumpGameWeather ChangedWeather);
    void EndWeatherChange();
};