//Saransh Beniwal
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WorkoutSystem.generated.h"

UENUM(BlueprintType)
enum class EWorkoutType : uint8 {
    BENCH_PRESS        UMETA(DisplayName = "Bench Press"),
    PUSHUPS           UMETA(DisplayName = "Push Ups"),
    DUMBBELL_FLYS     UMETA(DisplayName = "Dumbbell Flys"),
    INCLINE_PRESS     UMETA(DisplayName = "Incline Press"),
    DECLINE_PRESS     UMETA(DisplayName = "Decline Press"),
    BICEP_CURLS       UMETA(DisplayName = "Bicep Curls"),
    HAMMER_CURLS      UMETA(DisplayName = "Hammer Curls"),
    TRICEP_PUSHDOWN   UMETA(DisplayName = "Tricep Pushdown"),
    SKULL_CRUSHERS    UMETA(DisplayName = "Skull Crushers"),
    LATERAL_RAISES    UMETA(DisplayName = "Lateral Raises"),
    SQUATS            UMETA(DisplayName = "Squats"),
    LEG_PRESS         UMETA(DisplayName = "Leg Press"),
    DEADLIFTS         UMETA(DisplayName = "Deadlifts"),
    LUNGES            UMETA(DisplayName = "Lunges"),
    CALF_RAISES       UMETA(DisplayName = "Calf Raises"),
    
    NONE             UMETA(DisplayName = "None")
};

UCLASS()
class UWorkoutAnimHandler : public UObject {
    GENERATED_BODY()

private:
    UPROPERTY()
    TMap<EWorkoutType, UAnimMontage*> workout_anims;
    
    UPROPERTY()
    ACharacter* player;
    
    EWorkoutType current_workout;
    float rep_duration;
    
    int32 reps_done;
    int32 target_reps;
    
    float current_time;
    bool is_working_out;

public:
    UWorkoutAnimHandler();
    
    void Init(ACharacter* p);
    void LoadAnimations(); 
    
    void StartWorkout(EWorkoutType type, int32 reps);
    void StopWorkout();
    void UpdateWorkout(float DeltaTime);
    
    bool IsWorking() const { return is_working_out; }
    EWorkoutType GetCurrentWorkout() const { return current_workout; }
    static EWorkoutType GetRandomChestWorkout();
    static EWorkoutType GetRandomArmWorkout();
    static EWorkoutType GetRandomLegWorkout();
    
    static int32 GetWorkoutBaseXP(EWorkoutType type);
};