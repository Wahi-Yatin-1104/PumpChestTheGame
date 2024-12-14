#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API AInteractableObject : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInteractableObject();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle interaction
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact();

private:
    // Mesh component for the object
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* ObjectMesh;
};
