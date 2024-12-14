//Saransh Beniwal
#include "trackingworkout.h"

UWorkoutTracker::UWorkoutTracker() {
    got_1000_reps = false;
    got_100_workouts = false;
    hit_100_weight = false;
    
    total_workouts = 0;
    total_reps = 0;
    total_weight_lifted = 0.0f;
}

void UWorkoutTracker::LogWorkout(EWorkoutType type, int32 reps, int32 weight) {
    if(type == EWorkoutType::NONE || reps <= 0) return;
    FWorkoutSession session;
    session.type = type;
    session.reps = reps;
    session.weight = weight;
    session.xp_gained = UWorkoutAnimHandler::GetWorkoutBaseXP(type) * reps;
    session.time = FDateTime::Now();
    workout_history.Add(session);
    
    //update stats
    total_workouts++;
    total_reps += reps;
    total_weight_lifted += (weight * reps);
    
    int32& count = exercise_counts.FindOrAdd(type, 0);
    count++;
    
    UpdateAchievements(type, reps, weight);
    
    CheckAchievements();
    FString msg = FString::Printf(TEXT("%d reps of "), reps);
    switch(type) {
        case EWorkoutType::BENCH_PRESS:
            msg += TEXT("Bench Press");
            break;
        case EWorkoutType::DEADLIFTS:
            msg += TEXT("Deadlifts");
            break;
        default:
            msg += TEXT("exercise");
            break;
    }
    if(weight > 0) {
        msg += FString::Printf(TEXT(" at %d lbs"), weight);
    }
    UE_LOG(LogTemp, Warning, TEXT("Workout logged: %s"), *msg);
}
void UWorkoutTracker::UpdateAchievements(EWorkoutType type, int32 reps, int32 weight) {
    FWorkoutAchievement& Achievement = Achievements.FindOrAdd(type);
    
    Achievement.times_performed++;
    Achievement.total_reps += reps;
    
    bool new_Achievement = false;
    
    if(weight > Achievement.max_weight) {
        Achievement.max_weight = weight;
        new_Achievement = true;
        UE_LOG(LogTemp, Warning, TEXT("New weight Achievement: %d lbs!"), weight);
    }
    
    if(reps > Achievement.max_reps) {
        Achievement.max_reps = reps;
        new_Achievement = true;
        UE_LOG(LogTemp, Warning, TEXT("New rep Achievement: %d reps!"), reps);
    }
    
    if(Achievement.total_reps >= 1000 && !got_1000_reps) {
        UE_LOG(LogTemp, Warning, TEXT("ACHIEVEMENT: 1000 REPS ON ONE EXERCISE!"));
        got_1000_reps = true;
    }
}

void UWorkoutTracker::CheckAchievements() {
    if(total_workouts >= 100 && !got_100_workouts) {
        UE_LOG(LogTemp, Warning, TEXT("ACHIEVEMENT: 100 WORKOUTS COMPLETED!"));
        got_100_workouts = true;
    }

    for(auto& rec : Achievements) {
        if(rec.Value.max_weight >= 100 && !hit_100_weight) {
            UE_LOG(LogTemp, Warning, TEXT("ACHIEVEMENT: 100+ LBS ON AN EXERCISE!"));
            hit_100_weight = true;
            break;
        }
    }
    
    if(total_workouts % 50 == 0) {
        UE_LOG(LogTemp, Warning, TEXT("Milestone: %d total workouts!"), total_workouts);
    }
    
    if(total_reps % 1000 == 0) {
        UE_LOG(LogTemp, Warning, TEXT("Milestone: %d total reps!"), total_reps);
    }
}

TArray<FWorkoutSession> UWorkoutTracker::GetRecentWorkouts(int32 count) const {
    TArray<FWorkoutSession> recent;
    
    int32 start = FMath::Max(0, workout_history.Num() - count);
    for(int32 i = start; i < workout_history.Num(); i++) {
        recent.Add(workout_history[i]);
    }
    
    return recent;
}
TArray<FWorkoutSession> UWorkoutTracker::GetWorkoutsByType(EWorkoutType type) const {
    TArray<FWorkoutSession> filtered;
    
    for(const auto& workout : workout_history) {
        if(workout.type == type) {
            filtered.Add(workout);
        }
    }
    
    return filtered;
}

FWorkoutAchievement UWorkoutTracker::GetAchievementForExercise(EWorkoutType type) const {
    return Achievements.FindRef(type);
}

EWorkoutType UWorkoutTracker::GetFavoriteChestExercise() const {
    EWorkoutType fav = EWorkoutType::NONE;
    int32 max_count = 0;
    
    TArray<EWorkoutType> chest_exercises = {
        EWorkoutType::BENCH_PRESS,
        EWorkoutType::PUSHUPS,
        EWorkoutType::DUMBBELL_FLYS,
        EWorkoutType::INCLINE_PRESS,
        EWorkoutType::DECLINE_PRESS
    };
    
    for(auto exercise : chest_exercises) {
        if(int32* count = exercise_counts.Find(exercise)) {
            if(*count > max_count) {
                max_count = *count;
                fav = exercise;
            }
        }
    }
    
    return fav;
}
EWorkoutType UWorkoutTracker::GetFavoriteArmExercise() const {
    EWorkoutType fav = EWorkoutType::NONE;
    int32 max_count = 0;
    
    TArray<EWorkoutType> arm_exercises = {
        EWorkoutType::BICEP_CURLS,
        EWorkoutType::HAMMER_CURLS,
        EWorkoutType::TRICEP_PUSHDOWN,
        EWorkoutType::SKULL_CRUSHERS,
        EWorkoutType::LATERAL_RAISES
    };
    
    for(auto exercise : arm_exercises) {
        if(int32* count = exercise_counts.Find(exercise)) {
            if(*count > max_count) {
                max_count = *count;
                fav = exercise;
            }
        }
    }
    
    return fav;
}

EWorkoutType UWorkoutTracker::GetFavoriteLegExercise() const {
    EWorkoutType fav = EWorkoutType::NONE;
    int32 max_count = 0;
    TArray<EWorkoutType> leg_exercises = {
        EWorkoutType::SQUATS,
        EWorkoutType::LEG_PRESS,
        EWorkoutType::DEADLIFTS,
        EWorkoutType::LUNGES,
        EWorkoutType::CALF_RAISES
    };
    
    for(auto exercise : leg_exercises) {
        if(int32* count = exercise_counts.Find(exercise)) {
            if(*count > max_count) {
                max_count = *count;
                fav = exercise;
            }
        }
    }
    
    return fav;
}
//debuging
void UWorkoutTracker::PrintHistory() const {
    UE_LOG(LogTemp, Warning, TEXT("WORKOUT HISTORY"));
    for(const auto& workout : workout_history) {
        UE_LOG(LogTemp, Warning, TEXT("%s: %d reps at %d lbs (XP: %d)"),
            *workout.time.ToString(), workout.reps, workout.weight, workout.xp_gained);
    }
}
void UWorkoutTracker::PrintAchievements() const {
    UE_LOG(LogTemp, Warning, TEXT("AchievementS"));
    for(const auto& rec : Achievements) {
        UE_LOG(LogTemp, Warning, TEXT("%d: Max Weight: %d lbs, Max Reps: %d, Total Reps: %d"),
            (int32)rec.Key, rec.Value.max_weight, rec.Value.max_reps, rec.Value.total_reps);
    }
}

void UWorkoutTracker::PrintStats() const {
    UE_LOG(LogTemp, Warning, TEXT("WORKOUT"));
    UE_LOG(LogTemp, Warning, TEXT("Total Workouts: %d"), total_workouts);
    UE_LOG(LogTemp, Warning, TEXT("Total Reps: %d"), total_reps);
    UE_LOG(LogTemp, Warning, TEXT("Total Weight Lifted: %.1f lbs"), total_weight_lifted);
    
    EWorkoutType fav_chest = GetFavoriteChestExercise();
    EWorkoutType fav_arms = GetFavoriteArmExercise();
    EWorkoutType fav_legs = GetFavoriteLegExercise();
    
    UE_LOG(LogTemp, Warning, TEXT("Most/Favorite Exercises:"));
    UE_LOG(LogTemp, Warning, TEXT("Chest: %d"), (int32)fav_chest);
    UE_LOG(LogTemp, Warning, TEXT("Arms: %d"), (int32)fav_arms);
    UE_LOG(LogTemp, Warning, TEXT("Legs: %d"), (int32)fav_legs);
}