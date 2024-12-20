#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterCustomization.generated.h"

UCLASS()
class PUMPCHESTTHEGAME_API ACharacterCustomization : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACharacterCustomization();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to change character's clothing
    UFUNCTION(BlueprintCallable, Category = "Customization")
    void ChangeClothing(USkeletalMesh* NewClothing);

    // Function to change character's accessories
    UFUNCTION(BlueprintCallable, Category = "Customization")
    void ChangeAccessories(USkeletalMesh* NewAccessories);

private:
    // Skeletal mesh component for clothing
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* ClothingMesh;

    // Skeletal mesh component for accessories
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USkeletalMeshComponent* AccessoriesMesh;
};
