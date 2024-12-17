// WRITTEN BY YATIN WAHI

#include "QuestSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AQuestSystem::AQuestSystem()
{
    PrimaryActorTick.bCanEverTick = true;
    LastQuestCheckTime = 0.0f;
    QuestCheckInterval = 5.0f;
    TotalExperiencePoints = 0;
    CompletedQuestCount = 0;
    CurrentQuestChainLength = 0;
    LongestQuestChain = 0;
    QuestPoints = 0;
    DailyQuestsCompleted = 0;
    WeeklyQuestsCompleted = 0;
    InitializeDefaultQuests();
}

void AQuestSystem::BeginPlay()
{
    Super::BeginPlay();
    LoadQuestProgress();
    StartDailyQuestReset();
    StartWeeklyQuestReset();
}

void AQuestSystem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    LastQuestCheckTime += DeltaTime;
    
    if (LastQuestCheckTime >= QuestCheckInterval)
    {
        UpdateQuestTimers();
        CheckQuestChainProgress();
        LastQuestCheckTime = 0.0f;
    }
}

void AQuestSystem::InitializeDefaultQuests()
{
    TArray<FString> DefaultQuestTypes = {"Daily", "Weekly", "Story", "Side", "Hidden", "Challenge"};
    for (const FString& Type : DefaultQuestTypes)
    {
        FQuest NewQuest;
        NewQuest.QuestType = Type;
        NewQuest.Difficulty = 1;
        NewQuest.ExperienceReward = 100;
        NewQuest.TimeLimit = -1.0f;
        QuestTemplates.Add(NewQuest);
    }
}

void AQuestSystem::AddQuest(FQuest NewQuest)
{
    NewQuest.StartTime = FDateTime::Now();
    NewQuest.QuestID = GenerateQuestID();
    NewQuest.Progress = 0.0f;
    
    if (NewQuest.TimeLimit > 0)
    {
        NewQuest.EndTime = NewQuest.StartTime + FTimespan::FromHours(NewQuest.TimeLimit);
    }
    
    Quests.Add(NewQuest);
    BroadcastQuestUpdate(NewQuest, EQuestUpdateType::Added);
}

void AQuestSystem::CompleteQuest(FString QuestName)
{
    for (FQuest& Quest : Quests)
    {
        if (Quest.QuestName == QuestName && !Quest.bIsCompleted)
        {
            Quest.bIsCompleted = true;
            Quest.CompletionTime = FDateTime::Now();
            UpdateQuestMetrics(Quest);
            AwardQuestRewards(Quest);
            CheckQuestChainCompletion(Quest);
            BroadcastQuestUpdate(Quest, EQuestUpdateType::Completed);
            break;
        }
    }
}

void AQuestSystem::UpdateQuestProgress(FString QuestID, float Progress)
{
    for (FQuest& Quest : Quests)
    {
        if (Quest.QuestID == QuestID && !Quest.bIsCompleted)
        {
            Quest.Progress = FMath::Min(Progress, 100.0f);
            if (Quest.Progress >= 100.0f)
            {
                CompleteQuest(Quest.QuestName);
            }
            else
            {
                BroadcastQuestUpdate(Quest, EQuestUpdateType::ProgressUpdated);
            }
            break;
        }
    }
}

void AQuestSystem::AbandonQuest(FString QuestID)
{
    for (int32 i = 0; i < Quests.Num(); i++)
    {
        if (Quests[i].QuestID == QuestID && !Quests[i].bIsCompleted)
        {
            FQuest AbandonedQuest = Quests[i];
            AbandonedQuest.bIsAbandoned = true;
            BroadcastQuestUpdate(AbandonedQuest, EQuestUpdateType::Abandoned);
            Quests.RemoveAt(i);
            break;
        }
    }
}

void AQuestSystem::UpdateQuestTimers()
{
    FDateTime CurrentTime = FDateTime::Now();
    for (FQuest& Quest : Quests)
    {
        if (!Quest.bIsCompleted && Quest.TimeLimit > 0)
        {
            if (CurrentTime > Quest.EndTime)
            {
                Quest.bIsFailed = true;
                BroadcastQuestUpdate(Quest, EQuestUpdateType::Failed);
            }
        }
    }
}

void AQuestSystem::StartDailyQuestReset()
{
    FDateTime CurrentTime = FDateTime::Now();
    FDateTime NextReset = CurrentTime + FTimespan::FromDays(1);
    NextReset = FDateTime(NextReset.GetYear(), NextReset.GetMonth(), NextReset.GetDay(), 0, 0, 0);
    
    float SecondsUntilReset = (NextReset - CurrentTime).GetTotalSeconds();
    GetWorld()->GetTimerManager().SetTimer(DailyResetTimerHandle, this, &AQuestSystem::ResetDailyQuests, SecondsUntilReset, false);
}

void AQuestSystem::StartWeeklyQuestReset()
{
    FDateTime CurrentTime = FDateTime::Now();
    int32 DaysUntilMonday = (8 - static_cast<int32>(CurrentTime.GetDayOfWeek())) % 7;
    FDateTime NextReset = CurrentTime + FTimespan::FromDays(DaysUntilMonday);
    NextReset = FDateTime(NextReset.GetYear(), NextReset.GetMonth(), NextReset.GetDay(), 0, 0, 0);
    
    float SecondsUntilReset = (NextReset - CurrentTime).GetTotalSeconds();
    GetWorld()->GetTimerManager().SetTimer(WeeklyResetTimerHandle, this, &AQuestSystem::ResetWeeklyQuests, SecondsUntilReset, false);
}

void AQuestSystem::ResetDailyQuests()
{
    for (FQuest& Quest : Quests)
    {
        if (Quest.QuestType == "Daily")
        {
            Quest.bIsCompleted = false;
            Quest.Progress = 0.0f;
            Quest.StartTime = FDateTime::Now();
            if (Quest.TimeLimit > 0)
            {
                Quest.EndTime = Quest.StartTime + FTimespan::FromHours(Quest.TimeLimit);
            }
        }
    }
    DailyQuestsCompleted = 0;
    StartDailyQuestReset();
    BroadcastQuestUpdate(FQuest(), EQuestUpdateType::DailyReset);
}

void AQuestSystem::ResetWeeklyQuests()
{
    for (FQuest& Quest : Quests)
    {
        if (Quest.QuestType == "Weekly")
        {
            Quest.bIsCompleted = false;
            Quest.Progress = 0.0f;
            Quest.StartTime = FDateTime::Now();
            if (Quest.TimeLimit > 0)
            {
                Quest.EndTime = Quest.StartTime + FTimespan::FromHours(Quest.TimeLimit);
            }
        }
    }
    WeeklyQuestsCompleted = 0;
    StartWeeklyQuestReset();
    BroadcastQuestUpdate(FQuest(), EQuestUpdateType::WeeklyReset);
}

void AQuestSystem::UpdateQuestMetrics(const FQuest& CompletedQuest)
{
    CompletedQuestCount++;
    TotalExperiencePoints += CompletedQuest.ExperienceReward;
    QuestPoints += CalculateQuestPoints(CompletedQuest);
    
    if (CompletedQuest.QuestType == "Daily")
    {
        DailyQuestsCompleted++;
    }
    else if (CompletedQuest.QuestType == "Weekly")
    {
        WeeklyQuestsCompleted++;
    }
    
    SaveQuestProgress();
}

int32 AQuestSystem::CalculateQuestPoints(const FQuest& Quest)
{
    float TimeBonus = 1.0f;
    if (Quest.TimeLimit > 0)
    {
        float TimeRemaining = (Quest.EndTime - Quest.CompletionTime).GetTotalHours();
        TimeBonus = 1.0f + (TimeRemaining / Quest.TimeLimit);
    }
    
    return FMath::RoundToInt(Quest.ExperienceReward * Quest.Difficulty * TimeBonus);
}

void AQuestSystem::CheckQuestChainProgress()
{
    CurrentQuestChainLength++;
    if (CurrentQuestChainLength > LongestQuestChain)
    {
        LongestQuestChain = CurrentQuestChainLength;
    }
}

void AQuestSystem::CheckQuestChainCompletion(const FQuest& CompletedQuest)
{
    if (CompletedQuest.NextQuestID.IsEmpty())
    {
        CurrentQuestChainLength = 0;
    }
}

FString AQuestSystem::GenerateQuestID()
{
    return FGuid::NewGuid().ToString();
}

void AQuestSystem::BroadcastQuestUpdate(const FQuest& Quest, EQuestUpdateType UpdateType)
{
    OnQuestUpdated.Broadcast(Quest, UpdateType);
}

TArray<FQuest> AQuestSystem::GetQuestsByType(FString QuestType) const
{
    TArray<FQuest> FilteredQuests;
    for (const FQuest& Quest : Quests)
    {
        if (Quest.QuestType == QuestType)
        {
            FilteredQuests.Add(Quest);
        }
    }
    return FilteredQuests;
}

TArray<FQuest> AQuestSystem::GetActiveQuests() const
{
    TArray<FQuest> ActiveQuests;
    for (const FQuest& Quest : Quests)
    {
        if (!Quest.bIsCompleted && !Quest.bIsFailed && !Quest.bIsAbandoned)
        {
            ActiveQuests.Add(Quest);
        }
    }
    return ActiveQuests;
}

void AQuestSystem::SaveQuestProgress()
{}

void AQuestSystem::LoadQuestProgress()
{}