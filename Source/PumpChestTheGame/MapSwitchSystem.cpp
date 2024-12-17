// WRITTEN BY YATIN WAHI

#include "MapSwitchingSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "TimerManager.h"


AMapSwitchingSystem::AMapSwitchingSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    bIsLevelComplete = false;
    MapSwitchDelay = 3.0f; 
}


void AMapSwitchingSystem::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Map Switching System Initialized"));
}


void AMapSwitchingSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SimulateProgressBarChecks();
}


void AMapSwitchingSystem::CheckProgressBars(float StaminaBar, float StrengthBar, float EnduranceBar)
{
    if (StaminaBar >= 100.0f && StrengthBar >= 100.0f && EnduranceBar >= 100.0f && !bIsLevelComplete)
    {
        bIsLevelComplete = true;
        DisplayLevelCompleteMessage();
        

        FName NextMapName = "NextLevelMap"; 
        GetWorldTimerManager().SetTimer(MapSwitchTimerHandle, this, &AMapSwitchingSystem::HandleDelayedMapSwitch, MapSwitchDelay, false, MapSwitchDelay);
    }
    else if (!bIsLevelComplete)
    {
        UE_LOG(LogTemp, Log, TEXT("Progress Bars: Stamina: %.2f, Strength: %.2f, Endurance: %.2f"), StaminaBar, StrengthBar, EnduranceBar);
    }
}


void AMapSwitchingSystem::DisplayLevelCompleteMessage()
{
    FString Message = "Congratulations Level Complete!";
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
    }
    UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
}


void AMapSwitchingSystem::SwitchMap(FName NextMapName)
{
    if (!NextMapName.IsNone())
    {
        UGameplayStatics::OpenLevel(this, NextMapName);
        UE_LOG(LogTemp, Log, TEXT("Switching to map: %s"), *NextMapName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid map name provided for switching"));
    }
}


void AMapSwitchingSystem::HandleDelayedMapSwitch(FName NextMapName)
{
    SwitchMap(NextMapName);
}

void AMapSwitchingSystem::SimulateProgressBarChecks()
{
    static float Stamina = 0.0f;
    static float Strength = 0.0f;
    static float Endurance = 0.0f;


    Stamina = FMath::Clamp(Stamina + 0.1f, 0.0f, 100.0f);
    Strength = FMath::Clamp(Strength + 0.1f, 0.0f, 100.0f);
    Endurance = FMath::Clamp(Endurance + 0.1f, 0.0f, 100.0f);

    CheckProgressBars(Stamina, Strength, Endurance);
}
