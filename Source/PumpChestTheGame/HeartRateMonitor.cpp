/*
#include "HeartRateMonitor.h"
#include <opencv2/opencv.hpp>

// Sets default values
AHeartRateMonitor::AHeartRateMonitor()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    HeartRate = 0;
    bIsMonitoring = false;
}

// Called when the game starts or when spawned
void AHeartRateMonitor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AHeartRateMonitor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsMonitoring)
    {
        ProcessFrame();
    }
}

// Function to start the heart rate monitoring
void AHeartRateMonitor::StartMonitoring()
{
    VideoCapture.open(0); // Open the default camera
    if (VideoCapture.isOpened())
    {
        bIsMonitoring = true;
        UE_LOG(LogTemp, Log, TEXT("Heart rate monitoring started"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to open camera"));
    }
}

// Function to stop the heart rate monitoring
void AHeartRateMonitor::StopMonitoring()
{
    bIsMonitoring = false;
    VideoCapture.release();
    UE_LOG(LogTemp, Log, TEXT("Heart rate monitoring stopped"));
}

// Function to get the current heart rate
int32 AHeartRateMonitor::GetHeartRate() const
{
    return HeartRate;
}

// Function to process the camera frame
void AHeartRateMonitor::ProcessFrame()
{
    cv::Mat Frame;
    VideoCapture >> Frame; // Capture a frame

    if (!Frame.empty())
    {
        // Process the frame to estimate heart rate
        // This is a simplified example, actual implementation would involve more complex processing
        HeartRate = 60 + rand() % 40; // Random heart rate between 60 and 100 for demonstration

        UE_LOG(LogTemp, Log, TEXT("Current heart rate: %d"), HeartRate);
    }
}
*/