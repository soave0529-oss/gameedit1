#pragma once

#include "CoreMinimal.h"
#include "Core/JoseonTypes.h"
#include "QuestTypes.generated.h"

USTRUCT(BlueprintType)
struct FQuestStepData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StepId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestStepType Type = EQuestStepType::Kill;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TargetId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentCount = 0;
};

USTRUCT(BlueprintType)
struct FQuestRewardData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Money = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EFaction, float> FactionRepChanges;
};

USTRUCT(BlueprintType)
struct FQuestData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TitleKo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DescKo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestStepData> Steps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FQuestRewardData Rewards;
};

USTRUCT(BlueprintType)
struct FQuestRuntimeState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestState State = EQuestState::NotStarted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStepIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> StepProgress;
};
