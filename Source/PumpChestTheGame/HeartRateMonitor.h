/*
#pragma once



#include <opencv2/opencv.hpp>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "opencv2/core.hpp"
#include "HeartRateMonitor.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API AHeartRateMonitor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHeartRateMonitor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to start the heart rate monitoring
    UFUNCTION(BlueprintCallable, Category = "HeartRate")
    void StartMonitoring();

    // Function to stop the heart rate monitoring
    UFUNCTION(BlueprintCallable, Category = "HeartRate")
    void StopMonitoring();

    // Function to get the current heart rate
    UFUNCTION(BlueprintCallable, Category = "HeartRate")
    int32 GetHeartRate() const;

private:
    // Function to process the camera frame
    void ProcessFrame();

    // OpenCV video capture object
    cv::VideoCapture VideoCapture;

    // Current heart rate
    int32 HeartRate;

    // Flag to indicate if monitoring is active
    bool bIsMonitoring;
};
*/