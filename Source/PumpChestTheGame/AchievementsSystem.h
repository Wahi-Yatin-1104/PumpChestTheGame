#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AchievementsSystem.generated.h"

USTRUCT(BlueprintType)
struct FAchievement
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    FString AchievementName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    float Progress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    float MaxProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    FString UnlockDate;

    FAchievement()
    {
        AchievementName = "New Achievement";
        Description = "Default Description";
        bIsUnlocked = false;
        Progress = 0.0f;
        MaxProgress = 100.0f;
        UnlockDate = "Not Unlocked Yet";
    }
};

UCLASS()
class PUMPCHESTTHEGAME_API AAchievementsSystem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAchievementsSystem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to check and unlock achievements
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void CheckForAchievementUnlock(FString AchievementName, float ProgressValue);

    // Function to display unlocked achievements
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void DisplayUnlockedAchievements();

    // Function to reset achievements
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void ResetAchievements();

    // Function to list all achievements
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void ListAllAchievements();

private:
    // Array to store all achievements
    UPROPERTY(EditAnywhere, Category = "Achievements")
    TArray<FAchievement> AchievementsList;

    // Helper function to initialize achievements
    void InitializeAchievements();

    // Helper function to find an achievement by name
    FAchievement* FindAchievementByName(const FString& AchievementName);

    // Function to notify player when an achievement is unlocked
    void NotifyAchievementUnlocked(const FAchievement& UnlockedAchievement);

    // Function to save achievements data (placeholder for future implementation)
    void SaveAchievementsData();

    // Function to load achievements data (placeholder for future implementation)
    void LoadAchievementsData();
};