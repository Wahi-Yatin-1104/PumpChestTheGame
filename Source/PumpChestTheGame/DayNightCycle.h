#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

class ADirectionalLight;  // Forward declaration

UCLASS()
class PUMPCHESTTHEGAME_API ADayNightCycle : public AActor
{
    GENERATED_BODY()
    
public:    
    ADayNightCycle();
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Lighting")
    ADirectionalLight* SunLight;

    UPROPERTY(EditAnywhere, Category = "Time")
    float CurrentTime;

    UPROPERTY(EditAnywhere, Category = "Time")
    float TimeScale;

    UPROPERTY(EditAnywhere, Category = "Time")
    float DayLength;

    void UpdateSunPosition();
};