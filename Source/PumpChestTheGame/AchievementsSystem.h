// WRITTEN BY YATIN WAHI

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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    int32 PointValue;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
    int32 CurrentTier;

    FAchievement()
    {
        AchievementName = "New Achievement";
        Description = "Default Description";
        bIsUnlocked = false;
        Progress = 0.0f;
        MaxProgress = 100.0f;
        UnlockDate = "Not Unlocked Yet";
        PointValue = 0;
        CurrentTier = 0;
    }
};

UCLASS()
class PUMPCHESTTHEGAME_API AAchievementsSystem : public AActor
{
    GENERATED_BODY()

public:
    AAchievementsSystem();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void CheckForAchievementUnlock(FString AchievementName, float ProgressValue);

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void DisplayUnlockedAchievements();

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void ResetAchievements();

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void ListAllAchievements();

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void TrackWorkoutMetrics(float WorkoutDuration, float CaloriesBurned, bool PerfectForm);

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void UnlockSpecialAchievement(const FString& AchievementName);

private:
    UPROPERTY(EditAnywhere, Category = "Achievements")
    TArray<FAchievement> AchievementsList;

    UPROPERTY(EditAnywhere, Category = "Achievement Progress")
    float LastProgressUpdateTime;

    UPROPERTY(EditAnywhere, Category = "Achievement Progress")
    float ProgressCheckInterval;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    int32 ConsecutiveWorkoutDays;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    FString LastWorkoutDate;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    float TotalWorkoutTime;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    float MaxCaloriesBurnedInOneSession;

    UPROPERTY(EditAnywhere, Category = "Achievement Points")
    int32 TotalAchievementPoints;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    int32 CurrentStreak;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    int32 LongestStreak;

    UPROPERTY(EditAnywhere, Category = "Achievement Metrics")
    int32 PerfectWorkouts;

    void InitializeAchievements();
    FAchievement* FindAchievementByName(const FString& AchievementName);
    void NotifyAchievementUnlocked(const FAchievement& UnlockedAchievement);
    void UpdateAchievementTiers(FAchievement& Achievement);
    void NotifyTierProgress(const FAchievement& Achievement, int32 Tier);
    void UpdateDailyProgress();
    bool IsPlayerWorkingOut();
    void CheckForMetricBasedAchievements();
    void CheckForMilestoneAchievements();
    void SaveAchievementProgress();
    void LoadAchievementProgress();
};