#include "CombatSystem.h"

// Sets default values
ACombatSystem::ACombatSystem()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACombatSystem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACombatSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to perform a melee attack
void ACombatSystem::PerformMeleeAttack()
{
    HandleMeleeAttack();
}

// Function to perform a ranged attack
void ACombatSystem::PerformRangedAttack()
{
    HandleRangedAttack();
}

// Function to block an attack
void ACombatSystem::Block()
{
    HandleBlock();
}

// Function to dodge an attack
void ACombatSystem::Dodge()
{
    HandleDodge();
}

// Function to handle melee attack logic
void ACombatSystem::HandleMeleeAttack()
{
    // Melee attack logic here
    UE_LOG(LogTemp, Log, TEXT("Performed melee attack"));
}

// Function to handle ranged attack logic
void ACombatSystem::HandleRangedAttack()
{
    // Ranged attack logic here
    UE_LOG(LogTemp, Log, TEXT("Performed ranged attack"));
}

// Function to handle block logic
void ACombatSystem::HandleBlock()
{
    // Block logic here
    UE_LOG(LogTemp, Log, TEXT("Blocked attack"));
}

// Function to handle dodge logic
void ACombatSystem::HandleDodge()
{
    // Dodge logic here
    UE_LOG(LogTemp, Log, TEXT("Dodged attack"));
}
