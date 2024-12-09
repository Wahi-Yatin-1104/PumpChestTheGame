#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TestingAiController.generated.h"

UCLASS()
class LOCALTESTING_API ATestingAiController : public AAIController
{
    GENERATED_BODY()

public:
    // Sets default values for this controller's properties
    ATestingAiController();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to start patrolling
    void StartPatrolling();

    // Function to start attacking
    void StartAttacking();

    // Function to start fleeing
    void StartFleeing();

private:
    // Function to handle patrolling behavior
    void Patrol();

    // Function to handle attacking behavior
    void Attack();

    // Function to handle fleeing behavior
    void Flee();

    // Current state of the AI
    enum class EAIState
    {
        Patrolling,
        Attacking,
        Fleeing
    };

    EAIState CurrentState;
};
