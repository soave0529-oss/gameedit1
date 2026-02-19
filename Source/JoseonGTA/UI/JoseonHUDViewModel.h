#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Core/JoseonTypes.h"
#include "JoseonHUDViewModel.generated.h"

class AJoseonPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUIWantedChanged, int32, WantedLevel, float, WantedHeat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIReputationChanged, float, Reputation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUIFactionChanged, EFaction, Faction, float, Reputation);

UCLASS(BlueprintType)
class JOSEONGTA_API UJoseonHUDViewModel : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FUIWantedChanged OnWantedChanged;

    UPROPERTY(BlueprintAssignable)
    FUIReputationChanged OnReputationChanged;

    UPROPERTY(BlueprintAssignable)
    FUIFactionChanged OnFactionChanged;

    UFUNCTION(BlueprintCallable)
    void InitializeFromPlayerState(AJoseonPlayerState* InPlayerState);

private:
    UFUNCTION()
    void HandleWantedChanged(int32 NewLevel, float NewHeat);

    UFUNCTION()
    void HandleSocialChanged(ESocialClass NewClass, float NewReputation);

    UFUNCTION()
    void HandleFactionChanged(EFaction Faction, float Value);

    UPROPERTY()
    TObjectPtr<AJoseonPlayerState> BoundPlayerState;
};
