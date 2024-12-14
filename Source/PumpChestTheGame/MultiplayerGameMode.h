#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerGameMode.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API AMultiplayerGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    // Sets default values for this game mode's properties
    AMultiplayerGameMode();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle player joining
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void HandlePlayerJoin(APlayerController* NewPlayer);

    // Function to handle player leaving
    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void HandlePlayerLeave(APlayerController* LeavingPlayer);
};
