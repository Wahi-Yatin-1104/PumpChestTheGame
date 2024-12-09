#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventorySystem.generated.h"

UCLASS()
class LOCALTESTING_API AInventorySystem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInventorySystem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to add an item to the inventory
    void AddItem(FString ItemName);

    // Function to remove an item from the inventory
    void RemoveItem(FString ItemName);

    // Function to check if the inventory contains an item
    bool ContainsItem(FString ItemName) const;

    // Function to get the list of items in the inventory
    TArray<FString> GetInventoryItems() const;

private:
    // Array to store the inventory items
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
    TArray<FString> InventoryItems;
};
