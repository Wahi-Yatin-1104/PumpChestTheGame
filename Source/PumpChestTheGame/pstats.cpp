#include "PStats.h"

FPStats::FPStats() {
    BuffChest = 0;
    BuffGuns = 0;
    BuffLegs = 0;
    plevel = 1;  
    xp = 0;
}

FString FPStats::StatsToString() const {
    return FString::Printf(TEXT("%d,%d,%d,%d,%d"), 
        BuffChest, BuffGuns, BuffLegs, plevel, xp);
}

FPStats FPStats::LoadStats(const FString& data) {
    FPStats stats;
    TArray<FString> parsed;
    data.ParseIntoArray(parsed, TEXT(","), true);

    //making sure we have enough data
    if(parsed.Num() >= 5) {
        stats.BuffChest = FCString::Atoi(*parsed[0]);
        stats.BuffGuns = FCString::Atoi(*parsed[1]); 
        stats.BuffLegs = FCString::Atoi(*parsed[2]);
        stats.plevel = FCString::Atoi(*parsed[3]);
        stats.xp = FCString::Atoi(*parsed[4]);

        //fix invalid stats
        if(stats.BuffChest < 0) stats.BuffChest = 0;
        if(stats.BuffChest > 100) stats.BuffChest = 100;
        if(stats.BuffGuns < 0) stats.BuffGuns = 0;
        if(stats.BuffGuns > 100) stats.BuffGuns = 100;
        if(stats.BuffLegs < 0) stats.BuffLegs = 0;
        if(stats.BuffLegs > 100) stats.BuffLegs = 100;
        if(stats.plevel < 1) stats.plevel = 1;
        if(stats.plevel > 99) stats.plevel = 99;
        if(stats.xp < 0) stats.xp = 0;
    }

    return stats;
}

void FPStats::AddXP(int32 amount) {
    xp += amount;
    
    //need 1000 * level to level up
    while(xp >= plevel * 1000 && plevel < 99) {
        xp -= plevel * 1000;
        plevel++;
    }

    //cap xp at max
    if(plevel >= 99) {
        xp = 99000;  //max xp cap
    }
}

void FPStats::IncreaseBuff(int32& buff, int32 amount) {
    buff += amount;
    if(buff > 100)  //max buff is 100
        buff = 100;
}

void FPStats::DecreaseBuff(int32& buff, int32 amount) {
    buff -= amount;
    if(buff < 0)   //min buff is 0
        buff = 0;
}

int32 FPStats::GetBuffTotal() {
    return BuffChest + BuffGuns + BuffLegs;
}

bool FPStats::IsMaxed() {
    return BuffChest >= 100 && BuffGuns >= 100 && BuffLegs >= 100;
}

void FPStats::Reset() {
    //back to starting stats
    BuffChest = 0;
    BuffGuns = 0;
    BuffLegs = 0;
    plevel = 1;
    xp = 0;
}

bool FPStats::IsValid() {
    //check if stats are in valid range
    return BuffChest >= 0 && BuffChest <= 100 &&
           BuffGuns >= 0 && BuffGuns <= 100 && 
           BuffLegs >= 0 && BuffLegs <= 100 &&
           plevel >= 1 && plevel <= 99 &&
           xp >= 0;
}

FString FPStats::GetRank() {
    float avg = (BuffChest + BuffGuns + BuffLegs) / 3.0f;
    
    //return rank based on average buffs
    if(avg >= 90) return TEXT("Beast Mode");
    if(avg >= 75) return TEXT("Swole");
    if(avg >= 50) return TEXT("Getting Big");
    if(avg >= 25) return TEXT("Newbie Gains");
    return TEXT("Skipped Gym Day");
}