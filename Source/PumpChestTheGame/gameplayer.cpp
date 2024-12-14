//Saransh Beniwal
#include "gameplayer.h"
#include "Engine/Engine.h"

UPlayer::UPlayer() {
    chest_cooldown = 0;
    armsCooldown = 0;
    leg_cd = 0;
    
    level10unlocked = false;
    maxed_buff = false;
    workout100 = false;
    workoutCount = 0;
    combo = 0;
}

void UPlayer::check_level() {
    while(mystats.XPpoints >= mystats.PlayerLevel * 100) {
        mystats.PlayerLevel++;
        
        //level up message
        if(GEngine) {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, 
                FString::Printf(TEXT("Level Up! Now level %d!"), mystats.PlayerLevel));
        }
        
        //bonus every 5 level- do not have 5 levels yet for 426
        if(mystats.PlayerLevel % 5 == 0) {
            mystats.BuffChest += 2;
            mystats.BuffGuns += 2;
            mystats.BuffLegs += 2;
        }
        
        //hit max level
        if(mystats.PlayerLevel >= maxLevel) {
            mystats.PlayerLevel = maxLevel;
            break;
        }
    }
}

void UPlayer::handle_cooldowns(float deltaTime) {
    if(chest_cooldown > 0) chest_cooldown -= deltaTime;
    if(armsCooldown > 0) armsCooldown -= deltaTime;
    if(leg_cd > 0) leg_cd -= deltaTime;
    
    //fix negative cooldowns
    chest_cooldown = FMath::Max(0.0f, chest_cooldown);
    armsCooldown = FMath::Max(0.0f, armsCooldown);
    leg_cd = FMath::Max(0.0f, leg_cd);
}

bool UPlayer::canWorkout(FString muscle_group) {
    if(muscle_group == "chest" && chest_cooldown > 0) return false;
    if(muscle_group == "arms" && armsCooldown > 0) return false;
    if(muscle_group == "legs" && leg_cd > 0) return false;
    return true;
}

void UPlayer::workout(const FString& type, int32 power) {
    if(power <= 0) {
        UE_LOG(LogTemp, Warning, TEXT("Need more power bro!"));
        return;
    }

    if(!canWorkout(type)) {
        UE_LOG(LogTemp, Warning, TEXT("Too sore, wait for cooldown!"));
        return;
    }

    workoutCount++;

    if(type == "chest") {
        addBuff(mystats.BuffChest, power);
        chest_cooldown = cd_time; //chest is okay
    } 
    else if(type == "arms") {
        addBuff(mystats.BuffGuns, power);
        armsCooldown = cd_time * 0.75f;  //arms recover faster
    } 
    else if(type == "legs") {
        addBuff(mystats.BuffLegs, power);
        leg_cd = cd_time * 1.5f;  //legs need more rest
    } 
    else {
        UE_LOG(LogTemp, Warning, TEXT("What are you even training???"));
        return;
    }

    mystats.XPpoints += power;
    check_level();
    updateAchievements();

    if(GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, 
            FString::Printf(TEXT("+%d gains!"), power));
    }
}

void UPlayer::superWorkout(const FString& type) {
    if(!canWorkout(type)) {
        UE_LOG(LogTemp, Warning, TEXT("Not ready for super workout!"));
        return;
    }

    workout(type, 20);
    
    //more cooldown
    if(type == "chest") chest_cooldown *= 3;
    if(type == "arms") armsCooldown *= 3;
    if(type == "legs") leg_cd *= 3;
}

void UPlayer::WorkoutWithBuddy(const FString& type) {
    //workout with friend
    int32 base = 10;
    int32 bonus = FMath::RandRange(3, 7);
    workout(type, base + bonus);
}

void UPlayer::addBuff(int32& stat, int32 bonus) {
    stat += bonus;
    if(stat > maxBuff) {
        stat = maxBuff;
        UE_LOG(LogTemp, Warning, TEXT("MAXED OUT!!!"));
    }
}

void UPlayer::setPlayerStats(const Stats& stats) {
    mystats = stats;
    updateAchievements();
}

void UPlayer::printStats() const {
    UE_LOG(LogTemp, Warning, TEXT("=== GAINS STATUS ==="));
    UE_LOG(LogTemp, Warning, TEXT("Chest: %d/%d"), mystats.BuffChest, maxBuff);
    UE_LOG(LogTemp, Warning, TEXT("Arms: %d/%d"), mystats.BuffGuns, maxBuff);
    UE_LOG(LogTemp, Warning, TEXT("Legs: %d/%d"), mystats.BuffLegs, maxBuff);
    UE_LOG(LogTemp, Warning, TEXT("Level: %d"), mystats.PlayerLevel);
    UE_LOG(LogTemp, Warning, TEXT("XP: %d"), mystats.XPpoints);
    UE_LOG(LogTemp, Warning, TEXT("Workouts: %d"), workoutCount);
    UE_LOG(LogTemp, Warning, TEXT("Rank: %s"), *getRank());
}

int32 UPlayer::getTotalGains() const {
    return mystats.BuffChest + mystats.BuffGuns + mystats.BuffLegs;
}

void UPlayer::updateAchievements() {
    //level achievement
    if(mystats.PlayerLevel >= 10 && !level10unlocked) {
        level10unlocked = true;
        UE_LOG(LogTemp, Warning, TEXT("Achievement: Made it to level 10!"));
    }

    //max buff achievement
    if((mystats.BuffChest >= maxBuff || 
        mystats.BuffGuns >= maxBuff || 
        mystats.BuffLegs >= maxBuff) && !maxed_buff) {
        maxed_buff = true;
        UE_LOG(LogTemp, Warning, TEXT("Achievement: MAXIMUM GAINS!!!"));
    }

    //workout achievement
    if(workoutCount == 100 && !workout100) {
        workout100 = true;
        UE_LOG(LogTemp, Warning, TEXT("Achievement: 100 Workouts Done!"));
    }
}

bool UPlayer::hasAchievement(const FString& achievement_name) const {
    if(achievement_name == "lvl10") return level10unlocked;
    if(achievement_name == "maxed") return maxed_buff;
    if(achievement_name == "workouts") return workout100;
    return false;
}

void UPlayer::resetAll() {
    mystats.BuffChest = 0;
    mystats.BuffGuns = 0;
    mystats.BuffLegs = 0;
    mystats.PlayerLevel = 1;
    mystats.XPpoints = 0;
    
    workoutCount = 0;
    level10unlocked = false;
    maxed_buff = false;
    workout100 = false;
    combo = 0;
    
    UE_LOG(LogTemp, Warning, TEXT("Reset everything!"));
}

float UPlayer::getCooldown(const FString& muscle) const {
    if(muscle == "chest") return chest_cooldown;
    if(muscle == "arms") return armsCooldown;
    if(muscle == "legs") return leg_cd;
    return 0.0f;
}

FString UPlayer::getRank() const {
    int32 total = getTotalGains();
    
    if(total >= 290) return TEXT("GIGACHAD");
    if(total >= 250) return TEXT("BEAST");
    if(total >= 200) return TEXT("SWOLE");
    if(total >= 150) return TEXT("GETTING BIG");
    if(total >= 100) return TEXT("NEWBIE GAINS");
    if(total >= 50) return TEXT("STARTER");
    return TEXT("FRESH MEAT");
}

void UPlayer::addTestLevels(int32 howmany) {
    for(int32 i = 0; i < howmany; i++) {
        mystats.XPpoints += mystats.PlayerLevel * 100;
        check_level();
    }
}

void UPlayer::printDebug() const {
    UE_LOG(LogTemp, Warning, TEXT("DEBU"));
    UE_LOG(LogTemp, Warning, TEXT("cooldowns: %.1f %.1f %.1f"), 
        chest_cooldown, armsCooldown, leg_cd);
    UE_LOG(LogTemp, Warning, TEXT("workouts: %d"), workoutCount);
    UE_LOG(LogTemp, Warning, TEXT("achievs: %d %d %d"), 
        level10unlocked, maxed_buff, workout100);
}