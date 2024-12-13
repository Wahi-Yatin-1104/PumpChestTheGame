// Written by Yatin Wahi

#include "AchievementsSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Misc/DateTime.h"

// Sets default values
AAchievementsSystem::AAchievementsSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    InitializeAchievements();
}

// Called when the game starts or when spawned
void AAchievementsSystem::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Achievements System Initialized"));
}

// Called every frame
void AAchievementsSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to initialize the achievements list
void AAchievementsSystem::InitializeAchievements()
{
    FAchievement BenchPressMaster;
    BenchPressMaster.AchievementName = "Bench Press Master";
    BenchPressMaster.Description = "Complete a full bench press workout.";
    BenchPressMaster.MaxProgress = 100.0f;
    AchievementsList.Add(BenchPressMaster);

    FAchievement LegDayChampion;
    LegDayChampion.AchievementName = "Leg Day Champion";
    LegDayChampion.Description = "Complete a full leg workout.";
    LegDayChampion.MaxProgress = 100.0f;
    AchievementsList.Add(LegDayChampion);

    FAchievement StaminaSurvivor;
    StaminaSurvivor.AchievementName = "Stamina Survivor";
    StaminaSurvivor.Description = "Finish a workout with stamina at zero.";
    StaminaSurvivor.MaxProgress = 1.0f;
    AchievementsList.Add(StaminaSurvivor);

    FAchievement PowerLifter;
    PowerLifter.AchievementName = "Power Lifter";
    PowerLifter.Description = "Lift a total of 500 kg across all workouts.";
    PowerLifter.MaxProgress = 500.0f;
    AchievementsList.Add(PowerLifter);
}

// Function to check for achievement unlock
void AAchievementsSystem::CheckForAchievementUnlock(FString AchievementName, float ProgressValue)
{
    FAchievement* Achievement = FindAchievementByName(AchievementName);
    if (Achievement && !Achievement->bIsUnlocked)
    {
        Achievement->Progress += ProgressValue;

        if (Achievement->Progress >= Achievement->MaxProgress)
        {
            Achievement->bIsUnlocked = true;
            Achievement->UnlockDate = FDateTime::Now().ToString();
            NotifyAchievementUnlocked(*Achievement);
        }
    }
}

// Helper function to find an achievement by name
FAchievement* AAchievementsSystem::FindAchievementByName(const FString& AchievementName)
{
    for (FAchievement& Achievement : AchievementsList)
    {
        if (Achievement.AchievementName == AchievementName)
        {
            return &Achievement;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Achievement '%s' not found"), *AchievementName);
    return nullptr;
}

// Function to notify the player when an achievement is unlocked
void AAchievementsSystem::NotifyAchievementUnlocked(const FAchievement& UnlockedAchievement)
{
    FString Notification = FString::Printf(TEXT("Achievement Unlocked: %s - %s (Unlocked on: %s)"), *UnlockedAchievement.AchievementName, *UnlockedAchievement.Description, *UnlockedAchievement.UnlockDate);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Notification);
    }
    UE_LOG(LogTemp, Log, TEXT("%s"), *Notification);
}

// Function to display all unlocked achievements
void AAchievementsSystem::DisplayUnlockedAchievements()
{
    for (const FAchievement& Achievement : AchievementsList)
    {
        if (Achievement.bIsUnlocked)
        {
            FString UnlockedMessage = FString::Printf(TEXT("Unlocked: %s - %s (Unlocked on: %s)"), *Achievement.AchievementName, *Achievement.Description, *Achievement.UnlockDate);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, UnlockedMessage);
            }
            UE_LOG(LogTemp, Log, TEXT("%s"), *UnlockedMessage);
        }
    }
}

// Function to reset all achievements
void AAchievementsSystem::ResetAchievements()
{
    for (FAchievement& Achievement : AchievementsList)
    {
        Achievement.bIsUnlocked = false;
        Achievement.Progress = 0.0f;
        Achievement.UnlockDate = "Not Unlocked Yet";
    }
    UE_LOG(LogTemp, Log, TEXT("All achievements have been reset"));
}

// Function to list all achievements
void AAchievementsSystem::ListAllAchievements()
{
    for (const FAchievement& Achievement : AchievementsList)
    {
        FString AchievementInfo = FString::Printf(TEXT("Achievement: %s - %s | Progress: %.2f/%.2f"), *Achievement.AchievementName, *Achievement.Description, Achievement.Progress, Achievement.MaxProgress);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, AchievementInfo);
        }
        UE_LOG(LogTemp, Log, TEXT("%s"), *AchievementInfo);
    }
}
