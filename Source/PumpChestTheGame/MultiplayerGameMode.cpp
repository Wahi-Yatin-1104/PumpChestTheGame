#include "MultiplayerGameMode.h"

// Sets default values
AMultiplayerGameMode::AMultiplayerGameMode()
{
    // Set this game mode to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMultiplayerGameMode::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMultiplayerGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to handle player joining
void AMultiplayerGameMode::HandlePlayerJoin(APlayerController* NewPlayer)
{
    UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *NewPlayer->GetName());
    // Handle player joining logic here
}

// Function to handle player leaving
void AMultiplayerGameMode::HandlePlayerLeave(APlayerController* LeavingPlayer)
{
    UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *LeavingPlayer->GetName());
    // Handle player leaving logic here
}
