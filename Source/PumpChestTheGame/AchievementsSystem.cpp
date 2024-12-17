// WRITTEN BY YATIN WAHI

#include "AchievementsSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"

AAchievementsSystem::AAchievementsSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    InitializeAchievements();
    LastProgressUpdateTime = 0.0f;
    ProgressCheckInterval = 5.0f;
    ConsecutiveWorkoutDays = 0;
    LastWorkoutDate = "";
    TotalWorkoutTime = 0.0f;
    MaxCaloriesBurnedInOneSession = 0.0f;
    TotalAchievementPoints = 0;
    CurrentStreak = 0;
    LongestStreak = 0;
    PerfectWorkouts = 0;
}

void AAchievementsSystem::BeginPlay()
{
    Super::BeginPlay();
    LoadAchievementProgress();
}

void AAchievementsSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LastProgressUpdateTime += DeltaTime;
    
    if (LastProgressUpdateTime >= ProgressCheckInterval)
    {
        UpdateDailyProgress();
        LastProgressUpdateTime = 0.0f;
    }
}

void AAchievementsSystem::InitializeAchievements()
{
    FAchievement BenchPressMaster;
    BenchPressMaster.AchievementName = "Bench Press Master";
    BenchPressMaster.Description = "Complete a full bench press workout.";
    BenchPressMaster.MaxProgress = 100.0f;
    BenchPressMaster.PointValue = 50;
    AchievementsList.Add(BenchPressMaster);

    FAchievement LegDayChampion;
    LegDayChampion.AchievementName = "Leg Day Champion";
    LegDayChampion.Description = "Complete a full leg workout.";
    LegDayChampion.MaxProgress = 100.0f;
    LegDayChampion.PointValue = 50;
    AchievementsList.Add(LegDayChampion);

    FAchievement StaminaSurvivor;
    StaminaSurvivor.AchievementName = "Stamina Survivor";
    StaminaSurvivor.Description = "Finish a workout with stamina at zero.";
    StaminaSurvivor.MaxProgress = 1.0f;
    StaminaSurvivor.PointValue = 25;
    AchievementsList.Add(StaminaSurvivor);

    FAchievement PowerLifter;
    PowerLifter.AchievementName = "Power Lifter";
    PowerLifter.Description = "Lift a total of 500 kg across all workouts.";
    PowerLifter.MaxProgress = 500.0f;
    PowerLifter.PointValue = 100;
    AchievementsList.Add(PowerLifter);

    FAchievement EnduranceKing;
    EnduranceKing.AchievementName = "Endurance King";
    EnduranceKing.Description = "Complete 10 workouts without taking a break.";
    EnduranceKing.MaxProgress = 10.0f;
    EnduranceKing.PointValue = 150;
    AchievementsList.Add(EnduranceKing);

    FAchievement IronWill;
    IronWill.AchievementName = "Iron Will";
    IronWill.Description = "Maintain a perfect form for an entire workout session.";
    IronWill.MaxProgress = 1.0f;
    IronWill.PointValue = 75;
    AchievementsList.Add(IronWill);

    FAchievement CalorieCrusher;
    CalorieCrusher.AchievementName = "Calorie Crusher";
    CalorieCrusher.Description = "Burn 1000 calories in a single session.";
    CalorieCrusher.MaxProgress = 1000.0f;
    CalorieCrusher.PointValue = 200;
    AchievementsList.Add(CalorieCrusher);

    FAchievement GymRat;
    GymRat.AchievementName = "Gym Rat";
    GymRat.Description = "Spend 100 hours working out.";
    GymRat.MaxProgress = 360000.0f;
    GymRat.PointValue = 500;
    AchievementsList.Add(GymRat);

    FAchievement SupersetMaster;
    SupersetMaster.AchievementName = "Superset Master";
    SupersetMaster.Description = "Complete 50 supersets.";
    SupersetMaster.MaxProgress = 50.0f;
    SupersetMaster.PointValue = 125;
    AchievementsList.Add(SupersetMaster);

    FAchievement EarlyBird;
    EarlyBird.AchievementName = "Early Bird";
    EarlyBird.Description = "Complete 20 workouts before 7 AM.";
    EarlyBird.MaxProgress = 20.0f;
    EarlyBird.PointValue = 100;
    AchievementsList.Add(EarlyBird);
}

void AAchievementsSystem::CheckForAchievementUnlock(FString AchievementName, float ProgressValue)
{
    FAchievement* Achievement = FindAchievementByName(AchievementName);
    if (Achievement && !Achievement->bIsUnlocked)
    {
        Achievement->Progress += ProgressValue;
        UpdateAchievementTiers(*Achievement);

        if (Achievement->Progress >= Achievement->MaxProgress)
        {
            Achievement->bIsUnlocked = true;
            Achievement->UnlockDate = FDateTime::Now().ToString();
            TotalAchievementPoints += Achievement->PointValue;
            NotifyAchievementUnlocked(*Achievement);
            CheckForMilestoneAchievements();
        }
    }
}

void AAchievementsSystem::UpdateAchievementTiers(FAchievement& Achievement)
{
    float ProgressPercentage = (Achievement.Progress / Achievement.MaxProgress) * 100.0f;
    
    if (ProgressPercentage >= 75.0f && Achievement.CurrentTier < 3)
    {
        Achievement.CurrentTier = 3;
        NotifyTierProgress(Achievement, 3);
    }
    else if (ProgressPercentage >= 50.0f && Achievement.CurrentTier < 2)
    {
        Achievement.CurrentTier = 2;
        NotifyTierProgress(Achievement, 2);
    }
    else if (ProgressPercentage >= 25.0f && Achievement.CurrentTier < 1)
    {
        Achievement.CurrentTier = 1;
        NotifyTierProgress(Achievement, 1);
    }
}

void AAchievementsSystem::NotifyTierProgress(const FAchievement& Achievement, int32 Tier)
{
    FString TierMessage = FString::Printf(TEXT("%s - Reached Tier %d! (%.1f%% Complete)"), 
        *Achievement.AchievementName, 
        Tier,
        (Achievement.Progress / Achievement.MaxProgress) * 100.0f);
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TierMessage);
    }
}

void AAchievementsSystem::UpdateDailyProgress()
{
    FString CurrentDate = FDateTime::Now().ToString();
    
    if (LastWorkoutDate != CurrentDate && IsPlayerWorkingOut())
    {
        ConsecutiveWorkoutDays++;
        CurrentStreak++;
        if (CurrentStreak > LongestStreak)
        {
            LongestStreak = CurrentStreak;
        }
        LastWorkoutDate = CurrentDate;
    }
    else if (LastWorkoutDate != CurrentDate && !IsPlayerWorkingOut())
    {
        CurrentStreak = 0;
    }
    
    SaveAchievementProgress();
}

bool AAchievementsSystem::IsPlayerWorkingOut()
{
    return true;
}

void AAchievementsSystem::TrackWorkoutMetrics(float WorkoutDuration, float CaloriesBurned, bool PerfectForm)
{
    TotalWorkoutTime += WorkoutDuration;
    
    if (CaloriesBurned > MaxCaloriesBurnedInOneSession)
    {
        MaxCaloriesBurnedInOneSession = CaloriesBurned;
    }
    
    if (PerfectForm)
    {
        PerfectWorkouts++;
    }
    
    CheckForMetricBasedAchievements();
}

void AAchievementsSystem::CheckForMetricBasedAchievements()
{
    if (TotalWorkoutTime >= 360000.0f)
    {
        CheckForAchievementUnlock("Gym Rat", 360000.0f);
    }
    
    if (MaxCaloriesBurnedInOneSession >= 1000.0f)
    {
        CheckForAchievementUnlock("Calorie Crusher", 1000.0f);
    }
    
    if (ConsecutiveWorkoutDays >= 30)
    {
        CheckForAchievementUnlock("Dedication Master", 30.0f);
    }
}

void AAchievementsSystem::CheckForMilestoneAchievements()
{
    int32 UnlockedCount = 0;
    for (const FAchievement& Achievement : AchievementsList)
    {
        if (Achievement.bIsUnlocked)
        {
            UnlockedCount++;
        }
    }
    
    if (UnlockedCount >= 5)
    {
        UnlockSpecialAchievement("Achievement Hunter");
    }
    
    if (TotalAchievementPoints >= 1000)
    {
        UnlockSpecialAchievement("Points Master");
    }
}

void AAchievementsSystem::UnlockSpecialAchievement(const FString& AchievementName)
{
    FAchievement* Achievement = FindAchievementByName(AchievementName);
    if (Achievement && !Achievement->bIsUnlocked)
    {
        Achievement->bIsUnlocked = true;
        Achievement->Progress = Achievement->MaxProgress;
        Achievement->UnlockDate = FDateTime::Now().ToString();
        NotifyAchievementUnlocked(*Achievement);
    }
}

void AAchievementsSystem::SaveAchievementProgress()
{
}

void AAchievementsSystem::LoadAchievementProgress()
{
}

FAchievement* AAchievementsSystem::FindAchievementByName(const FString& AchievementName)
{
    for (FAchievement& Achievement : AchievementsList)
    {
        if (Achievement.AchievementName == AchievementName)
        {
            return &Achievement;
        }
    }
    return nullptr;
}

void AAchievementsSystem::NotifyAchievementUnlocked(const FAchievement& UnlockedAchievement)
{
    FString Notification = FString::Printf(TEXT("Achievement Unlocked: %s - %s (Unlocked on: %s)"), 
        *UnlockedAchievement.AchievementName, 
        *UnlockedAchievement.Description, 
        *UnlockedAchievement.UnlockDate);
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Notification);
    }
}

void AAchievementsSystem::DisplayUnlockedAchievements()
{
    for (const FAchievement& Achievement : AchievementsList)
    {
        if (Achievement.bIsUnlocked)
        {
            FString UnlockedMessage = FString::Printf(TEXT("Unlocked: %s - %s (Points: %d)"), 
                *Achievement.AchievementName, 
                *Achievement.Description, 
                Achievement.PointValue);
            
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, UnlockedMessage);
            }
        }
    }
}

void AAchievementsSystem::ResetAchievements()
{
    for (FAchievement& Achievement : AchievementsList)
    {
        Achievement.bIsUnlocked = false;
        Achievement.Progress = 0.0f;
        Achievement.UnlockDate = "Not Unlocked Yet";
        Achievement.CurrentTier = 0;
    }
    
    ConsecutiveWorkoutDays = 0;
    LastWorkoutDate = "";
    TotalWorkoutTime = 0.0f;
    MaxCaloriesBurnedInOneSession = 0.0f;
    TotalAchievementPoints = 0;
    CurrentStreak = 0;
    LongestStreak = 0;
    PerfectWorkouts = 0;
}

void AAchievementsSystem::ListAllAchievements()
{
    for (const FAchievement& Achievement : AchievementsList)
    {
        FString AchievementInfo = FString::Printf(TEXT("%s - %s | Progress: %.2f/%.2f | Tier: %d | Points: %d"), 
            *Achievement.AchievementName, 
            *Achievement.Description, 
            Achievement.Progress, 
            Achievement.MaxProgress,
            Achievement.CurrentTier,
            Achievement.PointValue);
        
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, AchievementInfo);
        }
    }
}