#include "Systems/QuestManager.h"
#include "JoseonGTA.h"
#include "Core/JoseonTypes.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool UQuestManager::LoadFromJsonString(const FString& JsonString)
{
    TSharedPtr<FJsonObject> Root;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogJoseon, Error, TEXT("퀘스트 JSON 파싱 실패"));
        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* QuestsArray;
    if (!Root->TryGetArrayField(TEXT("quests"), QuestsArray))
    {
        return false;
    }

    for (const TSharedPtr<FJsonValue>& Value : *QuestsArray)
    {
        const TSharedPtr<FJsonObject> QuestObj = Value->AsObject();
        if (!QuestObj.IsValid())
        {
            continue;
        }

        FQuestData Data;
        Data.QuestId = QuestObj->GetStringField(TEXT("quest_id"));
        Data.TitleKo = QuestObj->GetStringField(TEXT("title_ko"));
        Data.DescKo = QuestObj->GetStringField(TEXT("desc_ko"));

        const TArray<TSharedPtr<FJsonValue>>* StepsArray;
        if (QuestObj->TryGetArrayField(TEXT("steps"), StepsArray))
        {
            for (const TSharedPtr<FJsonValue>& StepValue : *StepsArray)
            {
                const TSharedPtr<FJsonObject> StepObj = StepValue->AsObject();
                FQuestStepData Step;
                Step.StepId = StepObj->GetStringField(TEXT("step_id"));
                Step.Type = ParseStepType(StepObj->GetStringField(TEXT("type")));
                Step.TargetId = StepObj->GetStringField(TEXT("target_id"));
                Step.Count = StepObj->GetIntegerField(TEXT("count"));
                Data.Steps.Add(Step);
            }
        }

        const TSharedPtr<FJsonObject>* RewardObj;
        if (QuestObj->TryGetObjectField(TEXT("rewards"), RewardObj))
        {
            Data.Rewards.Money = (*RewardObj)->GetIntegerField(TEXT("money"));
            const TSharedPtr<FJsonObject>* FactionChangesObj;
            if ((*RewardObj)->TryGetObjectField(TEXT("faction_rep_changes"), FactionChangesObj))
            {
                for (const auto& Pair : (*FactionChangesObj)->Values)
                {
                    const FString Key = Pair.Key;
                    const float ValueRep = static_cast<float>(Pair.Value->AsNumber());
                    if (Key == TEXT("government")) Data.Rewards.FactionRepChanges.Add(EFaction::Government, ValueRep);
                    else if (Key == TEXT("merchant_guild")) Data.Rewards.FactionRepChanges.Add(EFaction::MerchantGuild, ValueRep);
                    else if (Key == TEXT("bandits")) Data.Rewards.FactionRepChanges.Add(EFaction::Bandits, ValueRep);
                    else if (Key == TEXT("secret_society")) Data.Rewards.FactionRepChanges.Add(EFaction::SecretSociety, ValueRep);
                }
            }
        }

        QuestDB.Add(Data.QuestId, Data);
    }

    return true;
}

bool UQuestManager::LoadFromFile(const FString& RelativePath)
{
    FString JsonText;
    const FString FullPath = FPaths::ProjectContentDir() / RelativePath;
    if (!FFileHelper::LoadFileToString(JsonText, *FullPath))
    {
        UE_LOG(LogJoseon, Warning, TEXT("퀘스트 파일 로드 실패: %s"), *FullPath);
        return false;
    }
    return LoadFromJsonString(JsonText);
}

bool UQuestManager::StartQuest(const FString& QuestId)
{
    const FQuestData* Data = QuestDB.Find(QuestId);
    if (!Data)
    {
        return false;
    }

    FQuestRuntimeState& Runtime = QuestStates.FindOrAdd(QuestId);
    Runtime.QuestId = QuestId;
    Runtime.State = EQuestState::InProgress;
    Runtime.CurrentStepIndex = 0;
    Runtime.StepProgress.Init(0, Data->Steps.Num());
    return true;
}

bool UQuestManager::AdvanceStep(const FString& QuestId, const FString& StepId, int32 DeltaCount)
{
    FQuestRuntimeState* Runtime = QuestStates.Find(QuestId);
    const FQuestData* Data = QuestDB.Find(QuestId);
    if (!Runtime || !Data || Runtime->State != EQuestState::InProgress)
    {
        return false;
    }

    for (int32 i = 0; i < Data->Steps.Num(); ++i)
    {
        if (Data->Steps[i].StepId == StepId)
        {
            Runtime->StepProgress[i] = FMath::Clamp(Runtime->StepProgress[i] + DeltaCount, 0, Data->Steps[i].Count);
            if (Runtime->StepProgress[i] >= Data->Steps[i].Count)
            {
                Runtime->CurrentStepIndex = FMath::Max(Runtime->CurrentStepIndex, i + 1);
                if (Runtime->CurrentStepIndex >= Data->Steps.Num())
                {
                    return CompleteQuest(QuestId);
                }
            }
            return true;
        }
    }
    return false;
}

bool UQuestManager::CompleteQuest(const FString& QuestId)
{
    FQuestRuntimeState* Runtime = QuestStates.Find(QuestId);
    if (!Runtime)
    {
        return false;
    }

    Runtime->State = EQuestState::Completed;
    UE_LOG(LogJoseon, Log, TEXT("퀘스트 완료: %s"), *QuestId);
    return true;
}

EQuestState UQuestManager::GetQuestState(const FString& QuestId) const
{
    if (const FQuestRuntimeState* Runtime = QuestStates.Find(QuestId))
    {
        return Runtime->State;
    }
    return EQuestState::NotStarted;
}

void UQuestManager::ServerAdvanceQuest(const FString& QuestId, const FString& StepId, int32 DeltaCount)
{
    AdvanceStep(QuestId, StepId, DeltaCount);
}

EQuestStepType UQuestManager::ParseStepType(const FString& InType) const
{
    if (InType == TEXT("kill")) return EQuestStepType::Kill;
    if (InType == TEXT("deliver")) return EQuestStepType::Deliver;
    if (InType == TEXT("reach")) return EQuestStepType::Reach;
    if (InType == TEXT("steal")) return EQuestStepType::Steal;
    if (InType == TEXT("escort")) return EQuestStepType::Escort;
    return EQuestStepType::Kill;
}
