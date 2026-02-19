#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Core/JoseonTypes.h"
#include "Data/QuestTypes.h"
#include "JoseonSaveGame.generated.h"

UCLASS()
class JOSEONGTA_API UJoseonSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    FVector PlayerLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    FRotator PlayerRotation = FRotator::ZeroRotator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    ESocialClass SocialClass = ESocialClass::Sangmin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    float Reputation = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    int32 WantedLevel = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    float WantedHeat = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    TMap<EFaction, float> FactionReps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    TMap<FString, FQuestRuntimeState> QuestStates;
};
