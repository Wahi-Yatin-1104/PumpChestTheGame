#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatSystem.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API ACombatSystem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACombatSystem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to perform a melee attack
    void PerformMeleeAttack();

    // Function to perform a ranged attack
    void PerformRangedAttack();

    // Function to block an attack
    void Block();

    // Function to dodge an attack
    void Dodge();

private:
    // Function to handle melee attack logic
    void HandleMeleeAttack();

    // Function to handle ranged attack logic
    void HandleRangedAttack();

    // Function to handle block logic
    void HandleBlock();

    // Function to handle dodge logic
    void HandleDodge();
};
