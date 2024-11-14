#include "WeatherSystem.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"

AWeatherSystem::AWeatherSystem()
{
    PrimaryActorTick.bCanEverTick = true;

    TimeOfDay = 6.0f;
    SpeedOfTime = 60.0f;
    CurrentClimateOfGame = EPumpGameWeather::Sunny;
    SpeedOfWind = 0.0f;
    DensityOfFog = 0.01f;
    GameCurrentTemperature = 20.0f;
    GameCurrentSeason = TEXT("Spring");
    bGameWeatherSwitching = false;

    Rain = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Rain"));
    Rain->SetupAttachment(RootComponent);
    Rain->SetAutoActivate(false);

    Lightning = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lightning"));
    Lightning->SetupAttachment(RootComponent);
    Lightning->SetAutoActivate(false);
}

void AWeatherSystem::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> DirectionalLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), DirectionalLights);
    if (DirectionalLights.Num() > 0)
    {
        Sunlight = Cast<ADirectionalLight>(DirectionalLights[0]);
    }

    TArray<AActor*> SkyLights;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASkyLight::StaticClass(), SkyLights);
    if (SkyLights.Num() > 0)
    {
        Skylight = Cast<ASkyLight>(SkyLights[0]);
    }

    if (SoundOfRain)
    {
        GameWeatherAudio = UGameplayStatics::SpawnSound2D(this, SoundOfRain);
        if (GameWeatherAudio)
        {
            GameWeatherAudio->Stop();
        }
    }
}

void AWeatherSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeOfDay += DeltaTime * (SpeedOfTime / 3600.0f);
    if (TimeOfDay >= 24.0f)
    {
        TimeOfDay = 0.0f;
    }

    ChangeSun(DeltaTime);
    ChangeWeather(DeltaTime);
    ChangeFog();
    ChangeWind();

    if (CurrentClimateOfGame == EPumpGameWeather::Stormy && FMath::RandRange(0, 100) < 1)
    {
        Lightning->ActivateSystem();
        MakeThunder();
    }
}

void AWeatherSystem::ChangeSun(float DeltaTime)
{
    if (Sunlight)
    {
        float SunRotation = (TimeOfDay / 24.0f) * 360.0f - 90.0f;
        Sunlight->SetActorRotation(FRotator(SunRotation, 0.0f, 0.0f));
    }
}

void AWeatherSystem::ChangeWeather(float DeltaTime)
{
    if (!bGameWeatherSwitching)
    {
        if (FMath::RandRange(0, 1000) < 1)
        {
            EPumpGameWeather NewWeather = static_cast<EPumpGameWeather>(FMath::RandRange(0, 3));
            ChangeWeatherTo(NewWeather);
        }
    }
}

void AWeatherSystem::ChangeFog()
{
    if (CurrentClimateOfGame == EPumpGameWeather::Rainy || CurrentClimateOfGame == EPumpGameWeather::Stormy)
    {
        DensityOfFog = 0.1f;
        ColorOfFog = FLinearColor::Gray;
    }
    else
    {
        DensityOfFog = 0.01f;
        ColorOfFog = FLinearColor::Blue;
    }
}

void AWeatherSystem::ChangeWind()
{
    SpeedOfWind = (CurrentClimateOfGame == EPumpGameWeather::Sunny) ? 0.1f : FMath::RandRange(0.5f, 2.0f);
}

void AWeatherSystem::MakeThunder()
{
    if (SoundOfThunder)
    {
        UGameplayStatics::PlaySound2D(this, SoundOfThunder);
    }
}

void AWeatherSystem::ChangeWeatherTo(EPumpGameWeather NewWeather)
{
    if (CurrentClimateOfGame != NewWeather)
    {
        BeginWeatherChange(NewWeather);
    }
}

void AWeatherSystem::BeginWeatherChange(EPumpGameWeather ChangedWeather)
{
    bGameWeatherSwitching = true;

    CurrentClimateOfGame = ChangedWeather;

    if (ChangedWeather == EPumpGameWeather::Rainy || ChangedWeather == EPumpGameWeather::Stormy)
    {
        if (Rain)
        {
            Rain->Activate();
        }
        if (GameWeatherAudio)
        {
            GameWeatherAudio->Play();
        }
    }
    else
    {
        if (Rain)
        {
            Rain->Deactivate();
        }
        if (GameWeatherAudio)
        {
            GameWeatherAudio->Stop();
        }
    }

    bGameWeatherSwitching = false;
}

void AWeatherSystem::EndWeatherChange()
{
    bGameWeatherSwitching = false;
}