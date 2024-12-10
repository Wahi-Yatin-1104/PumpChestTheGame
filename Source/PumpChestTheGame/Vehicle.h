#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Vehicle.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API AVehicle : public APawn
{
    GENERATED_BODY()

public:
    AVehicle();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void DriveForward();

    void CheckForObstacles();

    void StopVehicle();

private:
    FTimerHandle TimerHandle;

    void PerformAction();

    UPROPERTY(EditAnywhere)
    float DriveSpeed;

    UPROPERTY(EditAnywhere)
    float DetectionRange;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* VehicleMesh;
};
