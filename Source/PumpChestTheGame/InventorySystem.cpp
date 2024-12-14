#include "InventorySystem.h"

// Sets default values
AInventorySystem::AInventorySystem()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInventorySystem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AInventorySystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to add an item to the inventory
void AInventorySystem::AddItem(FString ItemName)
{
    InventoryItems.Add(ItemName);
    UE_LOG(LogTemp, Log, TEXT("Added item: %s"), *ItemName);
}

// Function to remove an item from the inventory
void AInventorySystem::RemoveItem(FString ItemName)
{
    InventoryItems.Remove(ItemName);
    UE_LOG(LogTemp, Log, TEXT("Removed item: %s"), *ItemName);
}

// Function to check if the inventory contains an item
bool AInventorySystem::ContainsItem(FString ItemName) const
{
    return InventoryItems.Contains(ItemName);
}

// Function to get the list of items in the inventory
TArray<FString> AInventorySystem::GetInventoryItems() const
{
    return InventoryItems;
}
