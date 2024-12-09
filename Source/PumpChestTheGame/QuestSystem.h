#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystem.generated.h"

USTRUCT(BlueprintType)
struct FQuest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    bool bIsCompleted;
};

UCLASS()
class LOCALTESTING_API AQuestSystem : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AQuestSystem();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to add a quest
    void AddQuest(FQuest NewQuest);

    // Function to complete a quest
    void CompleteQuest(FString QuestName);

    // Function to get the list of quests
    TArray<FQuest> GetQuests() const;

private:
    // Array to store the quests
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", meta = (AllowPrivateAccess = "true"))
    TArray<FQuest> Quests;
};
