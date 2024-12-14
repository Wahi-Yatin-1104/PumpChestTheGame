#include "CharacterCustomization.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ACharacterCustomization::ACharacterCustomization()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create skeletal mesh components for customization
    ClothingMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClothingMesh"));
    ClothingMesh->SetupAttachment(RootComponent);

    AccessoriesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AccessoriesMesh"));
    AccessoriesMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacterCustomization::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACharacterCustomization::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to change character's clothing
void ACharacterCustomization::ChangeClothing(USkeletalMesh* NewClothing)
{
    if (NewClothing)
    {
        ClothingMesh->SetSkeletalMesh(NewClothing);
        UE_LOG(LogTemp, Log, TEXT("Changed clothing to: %s"), *NewClothing->GetName());
    }
}

// Function to change character's accessories
void ACharacterCustomization::ChangeAccessories(USkeletalMesh* NewAccessories)
{
    if (NewAccessories)
    {
        AccessoriesMesh->SetSkeletalMesh(NewAccessories);
        UE_LOG(LogTemp, Log, TEXT("Changed accessories to: %s"), *NewAccessories->GetName());
    }
}
