#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create mesh component
    ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
    RootComponent = ObjectMesh;
}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to handle interaction
void AInteractableObject::Interact()
{
    // Logic for interaction (e.g., picking up the object)
    UE_LOG(LogTemp, Log, TEXT("Interacted with object: %s"), *GetName());
}
