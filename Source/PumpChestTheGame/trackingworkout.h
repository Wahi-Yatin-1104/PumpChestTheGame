//Saransh Beniwal
#pragma once
#include "CoreMinimal.h"
#include "moreexercise.h"
#include "workout_tracker.generated.h"

USTRUCT(BlueprintType)
struct FWorkoutSession {
    GENERATED_BODY()

    UPROPERTY()
    EWorkoutType type;
    
    UPROPERTY()
    int32 reps;
    
    UPROPERTY()
    int32 weight;
    
    UPROPERTY()
    int32 xp_gained;
    
    UPROPERTY()
    FDateTime time;
    
    FWorkoutSession() : type(EWorkoutType::NONE), reps(0), weight(0), xp_gained(0) {
        time = FDateTime::Now();
    }
    
    FString ToString() const {
        return FString::Printf(TEXT("%d,%d,%d,%d,%s"), 
            (int32)type, reps, weight, xp_gained, *time.ToString());
    }
};

USTRUCT(BlueprintType)
struct FWorkoutAchievement {
    GENERATED_BODY()
    
    UPROPERTY()
    int32 max_weight;
    
    UPROPERTY()
    int32 max_reps;
    
    UPROPERTY()
    int32 total_reps;
    
    UPROPERTY()
    int32 times_performed;

    FWorkoutAchievement() : max_weight(0), max_reps(0), total_reps(0), times_performed(0) {}
};

UCLASS(BlueprintType)
class UWorkoutTracker : public UObject {
    GENERATED_BODY()
    
private:
    UPROPERTY()
    TArray<FWorkoutSession> workout_history;
    
    UPROPERTY()
    TMap<EWorkoutType, FWorkoutAchievement> Achievements;
    
    bool got_1000_reps;
    bool got_100_workouts;
    bool hit_100_weight;
    TMap<EWorkoutType, int32> exercise_counts;
    //stats
    int32 total_workouts;
    int32 total_reps;
    float total_weight_lifted;
    
public:
    UWorkoutTracker();
 
    void LogWorkout(EWorkoutType type, int32 reps, int32 weight = 0);
    void UpdateAchievements(EWorkoutType type, int32 reps, int32 weight);
    void CheckAchievements();
    
    int32 GetTotalWorkouts() const { return total_workouts; }
    int32 GetTotalReps() const { return total_reps; }
    float GetTotalWeight() const { return total_weight_lifted; }
    
    TArray<FWorkoutSession> GetRecentWorkouts(int32 count = 10) const;
    TArray<FWorkoutSession> GetWorkoutsByType(EWorkoutType type) const;
    FWorkoutAchievement GetAchievementForExercise(EWorkoutType type) const;
    
    EWorkoutType GetFavoriteChestExercise() const;
    EWorkoutType GetFavoriteArmExercise() const;
    EWorkoutType GetFavoriteLegExercise() const;
    
    //for debugging later
    void PrintHistory() const;
    void PrintAchievements() const;
    void PrintStats() const;
};