#include "TestingAiController.h"

// Sets default values
ATestingAiController::ATestingAiController()
{
    // Set this controller to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestingAiController::BeginPlay()
{
    Super::BeginPlay();
    StartPatrolling();
}

// Called every frame
void ATestingAiController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (CurrentState)
    {
    case EAIState::Patrolling:
        Patrol();
        break;
    case EAIState::Attacking:
        Attack();
        break;
    case EAIState::Fleeing:
        Flee();
        break;
    }
}

// Function to start patrolling
void ATestingAiController::StartPatrolling()
{
    CurrentState = EAIState::Patrolling;
}

// Function to start attacking
void ATestingAiController::StartAttacking()
{
    CurrentState = EAIState::Attacking;
}

// Function to start fleeing
void ATestingAiController::StartFleeing()
{
    CurrentState = EAIState::Fleeing;
}

// Function to handle patrolling behavior
void ATestingAiController::Patrol()
{
    // Patrolling logic here
    UE_LOG(LogTemp, Log, TEXT("Patrolling"));
}

// Function to handle attacking behavior
void ATestingAiController::Attack()
{
    // Attacking logic here
    UE_LOG(LogTemp, Log, TEXT("Attacking"));
}

// Function to handle fleeing behavior
void ATestingAiController::Flee()
{
    // Fleeing logic here
    UE_LOG(LogTemp, Log, TEXT("Fleeing"));
}
