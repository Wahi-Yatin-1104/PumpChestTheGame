#include "QuestSystem.h"

// Sets default values
AQuestSystem::AQuestSystem()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestSystem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AQuestSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to add a quest
void AQuestSystem::AddQuest(FQuest NewQuest)
{
    Quests.Add(NewQuest);
    UE_LOG(LogTemp, Log, TEXT("Added quest: %s"), *NewQuest.QuestName);
}

// Function to complete a quest
void AQuestSystem::CompleteQuest(FString QuestName)
{
    for (FQuest& Quest : Quests)
    {
        if (Quest.QuestName == QuestName)
        {
            Quest.bIsCompleted = true;
            UE_LOG(LogTemp, Log, TEXT("Completed quest: %s"), *QuestName);
            break;
        }
    }
}

// Function to get the list of quests
TArray<FQuest> AQuestSystem::GetQuests() const
{
    return Quests;
}
