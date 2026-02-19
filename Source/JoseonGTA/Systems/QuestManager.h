#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/QuestTypes.h"
#include "QuestManager.generated.h"

UCLASS()
class JOSEONGTA_API UQuestManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    bool LoadFromJsonString(const FString& JsonString);

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    bool LoadFromFile(const FString& RelativePath);

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    bool StartQuest(const FString& QuestId);

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    bool AdvanceStep(const FString& QuestId, const FString& StepId, int32 DeltaCount);

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    bool CompleteQuest(const FString& QuestId);

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    EQuestState GetQuestState(const FString& QuestId) const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Quest")
    void ServerAdvanceQuest(const FString& QuestId, const FString& StepId, int32 DeltaCount);

    const TMap<FString, FQuestRuntimeState>& GetQuestStates() const { return QuestStates; }
    void SetQuestStates(const TMap<FString, FQuestRuntimeState>& InStates) { QuestStates = InStates; }

private:
    EQuestStepType ParseStepType(const FString& InType) const;

    UPROPERTY()
    TMap<FString, FQuestData> QuestDB;

    UPROPERTY()
    TMap<FString, FQuestRuntimeState> QuestStates;
};
