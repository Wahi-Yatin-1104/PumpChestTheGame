//Saransh Beniwal
#pragma once
#include "pstats.h"
#include "CoreMinimal.h"
#include <string>
#include "player.generated.h"

UCLASS(Blueprintable)
class UPlayer : public UObject {
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Stats")
    Stats mystats;

    //cooldowns
    float chest_cooldown;   
    float armsCooldown;  
    float leg_cd;    
    
    //max stuff
    const int32 maxLevel = 100;
    const int32 maxBuff = 100;
    const float cd_time = 30.0f;

    void check_level();
    void handle_cooldowns(float deltaTime);
    bool canWorkout(FString muscle_group);
    void addBuff(int32& stat, int32 bonus);
    
    bool level10unlocked;
    bool maxed_buff;
    bool workout100;
    int32 workoutCount;
    int combo;

public:
    UPlayer();

    UFUNCTION(BlueprintCallable, Category = "Workouts")
    void workout(const FString& type, int32 power);
    
    UFUNCTION(BlueprintCallable, Category = "Workouts")
    void superWorkout(const FString& type);
    
    UFUNCTION(BlueprintCallable, Category = "Workouts")
    void WorkoutWithBuddy(const FString& type);
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    Stats getStats() const { return mystats; }
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void setPlayerStats(const Stats& stats);
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void printStats() const;
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 getTotalGains() const;
    
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void updateAchievements();
    
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    bool hasAchievement(const FString& achievement_name) const;
    
    UFUNCTION(BlueprintCallable, Category = "Utils")
    void resetAll();
    
    UFUNCTION(BlueprintCallable, Category = "Utils") 
    float getCooldown(const FString& muscle) const;
    
    UFUNCTION(BlueprintCallable, Category = "Utils")
    FString getRank() const;
    
    //debug
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void addTestLevels(int32 howmany);
    
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void printDebug() const;

    //later
    //void useProtein();
    //void addCombo();
    //int getScore();
};