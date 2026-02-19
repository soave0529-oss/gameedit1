#pragma once

#include "CoreMinimal.h"
#include "Core/JoseonTypes.h"
#include "GameFramework/PlayerState.h"
#include "JoseonPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSocialClassChanged, ESocialClass, NewClass, float, NewReputation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWantedStateChanged, int32, NewWantedLevel, float, NewWantedHeat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFactionRepChanged, EFaction, Faction, float, NewValue);

UCLASS()
class JOSEONGTA_API AJoseonPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    AJoseonPlayerState();

    UPROPERTY(BlueprintAssignable, Category="Joseon|Events")
    FOnSocialClassChanged OnSocialClassChanged;

    UPROPERTY(BlueprintAssignable, Category="Joseon|Events")
    FOnWantedStateChanged OnWantedStateChanged;

    UPROPERTY(BlueprintAssignable, Category="Joseon|Events")
    FOnFactionRepChanged OnFactionRepChanged;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    ESocialClass GetSocialClass() const { return SocialClass; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetReputation() const { return Reputation; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    int32 GetWantedLevel() const { return WantedLevel; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    float GetWantedHeat() const { return WantedHeat; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Faction")
    float GetFactionRep(EFaction Faction) const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetNpcReactionBias() const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetTaxRate() const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetWantedGainMultiplier() const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetShopPriceMultiplier() const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    int32 GetDialogueAccessTier() const;

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Social")
    void ServerSetSocialClass(ESocialClass InClass);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Social")
    void ServerSetReputation(float InValue);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Wanted")
    void ServerAddWantedHeat(float DeltaHeat);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Wanted")
    void ServerSetWantedHeat(float InHeat);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Faction")
    void ServerSetFactionRep(EFaction Faction, float NewRep);

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Faction")
    void ServerAddFactionRep(EFaction Faction, float Delta);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    UPROPERTY(ReplicatedUsing=OnRep_SocialData, EditAnywhere, BlueprintReadOnly, Category="Joseon|Social")
    ESocialClass SocialClass = ESocialClass::Sangmin;

    UPROPERTY(ReplicatedUsing=OnRep_SocialData, EditAnywhere, BlueprintReadOnly, Category="Joseon|Social")
    float Reputation = 0.f;

    UPROPERTY(ReplicatedUsing=OnRep_WantedData, BlueprintReadOnly, Category="Joseon|Wanted")
    int32 WantedLevel = 0;

    UPROPERTY(ReplicatedUsing=OnRep_WantedData, BlueprintReadOnly, Category="Joseon|Wanted")
    float WantedHeat = 0.f;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Joseon|Faction")
    TMap<EFaction, float> FactionReps;

    UFUNCTION()
    void OnRep_SocialData();

    UFUNCTION()
    void OnRep_WantedData();

    void RecalculateWantedLevel();
};
