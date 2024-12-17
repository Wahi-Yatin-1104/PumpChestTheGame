// WRITTEN BY YATIN WAHI

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapSwitchingSystem.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API AMapSwitchingSystem : public AActor
{
    GENERATED_BODY()
public:
    AMapSwitchingSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Map Switching")
    void CheckProgressBars(float StaminaBar, float StrengthBar, float EnduranceBar);

    UFUNCTION(BlueprintCallable, Category = "Map Switching")
    void SwitchMap(FName NextMapName);

    UFUNCTION(BlueprintCallable, Category = "Map Switching")
    void DisplayLevelCompleteMessage();

private:
    bool bIsLevelComplete;
    FTimerHandle MapSwitchTimerHandle;
    float MapSwitchDelay;
    void HandleDelayedMapSwitch(FName NextMapName);
    void SimulateProgressBarChecks();
};