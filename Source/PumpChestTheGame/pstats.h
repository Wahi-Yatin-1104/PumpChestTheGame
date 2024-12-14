//Saransh Beniwal
#pragma once
#include "CoreMinimal.h"
#include "PStats.generated.h"

USTRUCT(BlueprintType)
struct FPStats {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 BuffChest; //big chest

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") 
    int32 BuffGuns; //biceps

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 BuffLegs; //leg day

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 plevel; //current level

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats") 
    int32 xp;

    FPStats();

    FString StatsToString() const;
    static FPStats LoadStats(const FString& data);
    void AddXP(int32 amount);
    void IncreaseBuff(int32& buff, int32 amount);
    void DecreaseBuff(int32& buff, int32 amount);
    int32 GetBuffTotal();
    bool IsMaxed();
    void Reset();
    bool IsValid();
    FString GetRank();
};