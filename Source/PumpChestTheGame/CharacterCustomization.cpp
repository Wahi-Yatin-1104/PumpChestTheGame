#include "CharacterCustomization.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"

// Sets default values
ACharacterCustomization::ACharacterCustomization()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize Clothing Mesh
    ClothingMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClothingMesh"));
    ClothingMesh->SetupAttachment(RootComponent);

    // Initialize Accessories Mesh
    AccessoriesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AccessoriesMesh"));
    AccessoriesMesh->SetupAttachment(RootComponent);

    // Initialize Hairstyle Mesh
    HairstyleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairstyleMesh"));
    HairstyleMesh->SetupAttachment(RootComponent);

    // Set default eye color
    DefaultEyeColor = FLinearColor::Black;
}

// Called when the game starts or when spawned
void ACharacterCustomization::BeginPlay()
{
    Super::BeginPlay();

    // Initialize dynamic material for eyes
    if (ClothingMesh && ClothingMesh->GetMaterial(0))
    {
        EyeMaterial = UMaterialInstanceDynamic::Create(ClothingMesh->GetMaterial(0), this);
        ClothingMesh->SetMaterial(0, EyeMaterial);
    }
}

// Called every frame
void ACharacterCustomization::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to change character's clothing
void ACharacterCustomization::ChangeClothing(USkeletalMesh* NewClothing)
{
    if (NewClothing && ClothingMesh)
    {
        ClothingMesh->SetSkeletalMesh(NewClothing);
        UE_LOG(LogTemp, Log, TEXT("Changed clothing to: %s"), *NewClothing->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid clothing mesh or ClothingMesh component is null"));
    }
}

// Function to change character's accessories
void ACharacterCustomization::ChangeAccessories(USkeletalMesh* NewAccessories)
{
    if (NewAccessories && AccessoriesMesh)
    {
        AccessoriesMesh->SetSkeletalMesh(NewAccessories);
        UE_LOG(LogTemp, Log, TEXT("Changed accessories to: %s"), *NewAccessories->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid accessories mesh or AccessoriesMesh component is null"));
    }
}

// Function to change character's hairstyle
void ACharacterCustomization::ChangeHairstyle(USkeletalMesh* NewHairstyle)
{
    if (NewHairstyle && HairstyleMesh)
    {
        HairstyleMesh->SetSkeletalMesh(NewHairstyle);
        UE_LOG(LogTemp, Log, TEXT("Changed hairstyle to: %s"), *NewHairstyle->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid hairstyle mesh or HairstyleMesh component is null"));
    }
}

// Function to change character's eye color
void ACharacterCustomization::ChangeEyeColor(FLinearColor NewEyeColor)
{
    if (EyeMaterial)
    {
        EyeMaterial->SetVectorParameterValue(TEXT("EyeColor"), NewEyeColor);
        UE_LOG(LogTemp, Log, TEXT("Changed eye color"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eye material not initialized"));
    }
}

// Function to reset character customization to default
void ACharacterCustomization::ResetToDefault()
{
    if (DefaultClothing)
    {
        ClothingMesh->SetSkeletalMesh(DefaultClothing);
    }
    if (DefaultAccessories)
    {
        AccessoriesMesh->SetSkeletalMesh(DefaultAccessories);
    }
    if (DefaultHairstyle)
    {
        HairstyleMesh->SetSkeletalMesh(DefaultHairstyle);
    }
    if (EyeMaterial)
    {
        EyeMaterial->SetVectorParameterValue(TEXT("EyeColor"), DefaultEyeColor);
    }
    UE_LOG(LogTemp, Log, TEXT("Character customization reset to default"));
}
