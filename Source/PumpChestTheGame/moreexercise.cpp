//Saransh Beniwal
#include "moreexercise.h"
#include "GameFramework/Character.h"

UWorkoutAnimHandler::UWorkoutAnimHandler() {
    player = nullptr;
    current_workout = EWorkoutType::NONE;
    rep_duration = 2.0f;
    reps_done = 0;
    target_reps = 0;
    current_time = 0.0f;
    is_working_out = false;
}
 
void UWorkoutAnimHandler::Init(ACharacter* p) {
    player = p;
    LoadAnimations();
}

void UWorkoutAnimHandler::LoadAnimations() {
    
    workout_anims.Add(EWorkoutType::BENCH_PRESS, 
        //LoadObject()
    workout_anims.Add(EWorkoutType::PUSHUPS,
        //LoadObject()
        
    workout_anims.Add(EWorkoutType::BICEP_CURLS,
        //LoadObject()
    workout_anims.Add(EWorkoutType::HAMMER_CURLS,
        
    workout_anims.Add(EWorkoutType::SQUATS,
        //LoadObject()
    workout_anims.Add(EWorkoutType::LEG_PRESS,
        //LoadObject()
}

void UWorkoutAnimHandler::StartWorkout(EWorkoutType type, int32 reps) {
    if(!player || type == EWorkoutType::NONE) return;
    
    if(is_working_out) {
        UE_LOG(LogTemp, Warning, TEXT("Already doing a workout bro!"));
        return;
    }
    
    UAnimMontage* anim = workout_anims.FindRef(type);
    if(!anim) {
        UE_LOG(LogTemp, Warning, TEXT("Missing animation for workout!"));
        return;
    }
    
    //start workout
    current_workout = type;
    target_reps = reps;
    reps_done = 0;
    current_time = 0.0f;
    is_working_out = true;
    
    player->PlayAnimMontage(anim);
    
    switch(type) {
        case EWorkoutType::BENCH_PRESS:
            UE_LOG(LogTemp, Warning, TEXT("Time to move some weight!"));
            break;
        case EWorkoutType::DEADLIFTS:
            UE_LOG(LogTemp, Warning, TEXT("LIGHT WEIGHT BABY!"));
            break;
        case EWorkoutType::SQUATS:
            UE_LOG(LogTemp, Warning, TEXT("Never skip leg day!"));
            break;
        case EWorkoutType::BICEP_CURLS:
            UE_LOG(LogTemp, Warning, TEXT("Sun's out, guns out!"));
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Let's get this workout started!"));
            break;
    }
}

void UWorkoutAnimHandler::StopWorkout() {
    if(!is_working_out) return;
    
    if(player && workout_anims.Contains(current_workout)) {
        player->StopAnimMontage(workout_anims[current_workout]);
    }
    
    //rset game stat
    current_workout = EWorkoutType::NONE;
    is_working_out = false;
    reps_done = 0;
    target_reps = 0;
    current_time = 0.0f;
}

void UWorkoutAnimHandler::UpdateWorkout(float DeltaTime) {
    if(!is_working_out || !player) return;
    
    current_time += DeltaTime;
    
    if(current_time >= rep_duration) {
        reps_done++;
        current_time = 0.0f;
        
        if(reps_done >= target_reps) {
            StopWorkout();
            
            switch(FMath::RandRange(0, 4)) {
                case 0:
                    UE_LOG(LogTemp, Warning, TEXT("YEAH BUDDY!"));
                    break;
                case 1:
                    UE_LOG(LogTemp, Warning, TEXT("Nothin"));
                    break;
                case 2:
                    UE_LOG(LogTemp, Warning, TEXT("nothing but a workout"));
                    break;
                case 3:
                    UE_LOG(LogTemp, Warning, TEXT("Lightweight easy!"));
                    break;
                default:
                    UE_LOG(LogTemp, Warning, TEXT("Great workout!"));
                    break;
            }
        }
        else if(workout_anims.Contains(current_workout)) {
            player->PlayAnimMontage(workout_anims[current_workout]);
        }
    }
}

EWorkoutType UWorkoutAnimHandler::GetRandomChestWorkout() {
    switch(FMath::RandRange(0, 4)) {
        case 0: return EWorkoutType::BENCH_PRESS;
        case 1: return EWorkoutType::PUSHUPS;
        case 2: return EWorkoutType::DUMBBELL_FLYS;
        case 3: return EWorkoutType::INCLINE_PRESS;
        default: return EWorkoutType::DECLINE_PRESS;
    }
}

EWorkoutType UWorkoutAnimHandler::GetRandomArmWorkout() {
    switch(FMath::RandRange(0, 4)) {
        case 0: return EWorkoutType::BICEP_CURLS;
        case 1: return EWorkoutType::HAMMER_CURLS;
        case 2: return EWorkoutType::TRICEP_PUSHDOWN;
        case 3: return EWorkoutType::SKULL_CRUSHERS;
        default: return EWorkoutType::LATERAL_RAISES;
    }
}
EWorkoutType UWorkoutAnimHandler::GetRandomLegWorkout() {
    switch(FMath::RandRange(0, 4)) {
        case 0: return EWorkoutType::SQUATS;
        case 1: return EWorkoutType::LEG_PRESS;
        case 2: return EWorkoutType::DEADLIFTS;
        case 3: return EWorkoutType::LUNGES;
        default: return EWorkoutType::CALF_RAISES;
    }
}

int32 UWorkoutAnimHandler::GetWorkoutBaseXP(EWorkoutType type) {
    switch(type) {
        case EWorkoutType::BENCH_PRESS:
            return 15;
        case EWorkoutType::DEADLIFTS:
            return 20;
        case EWorkoutType::SQUATS:
            return 18;  
        case EWorkoutType::INCLINE_PRESS:
        case EWorkoutType::DECLINE_PRESS:
        case EWorkoutType::LEG_PRESS:
            return 12;
        case EWorkoutType::BICEP_CURLS:
        case EWorkoutType::HAMMER_CURLS:
        case EWorkoutType::TRICEP_PUSHDOWN:
        case EWorkoutType::SKULL_CRUSHERS:
        case EWorkoutType::LATERAL_RAISES:
        case EWorkoutType::DUMBBELL_FLYS:
            return 8;
            
        case EWorkoutType::PUSHUPS:
        case EWorkoutType::LUNGES:
        case EWorkoutType::CALF_RAISES:
            return 5;
            
        default:
            return 0;
    }
}
