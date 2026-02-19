#include "Core/JoseonPlayerState.h"
#include "JoseonGTA.h"
#include "Net/UnrealNetwork.h"

AJoseonPlayerState::AJoseonPlayerState()
{
    bReplicates = true;
    FactionReps.Add(EFaction::Government, 0.f);
    FactionReps.Add(EFaction::MerchantGuild, 0.f);
    FactionReps.Add(EFaction::Bandits, 0.f);
    FactionReps.Add(EFaction::SecretSociety, 0.f);
}

float AJoseonPlayerState::GetFactionRep(EFaction Faction) const
{
    if (const float* Found = FactionReps.Find(Faction))
    {
        return *Found;
    }
    return 0.f;
}

float AJoseonPlayerState::GetNpcReactionBias() const
{
    const float ClassBias = (SocialClass == ESocialClass::Noble) ? 20.f : (SocialClass == ESocialClass::Outlaw ? -30.f : 0.f);
    return FMath::Clamp(ClassBias + Reputation * 0.4f, -100.f, 100.f);
}

float AJoseonPlayerState::GetTaxRate() const
{
    const float Base = 0.1f;
    const float ClassModifier = (SocialClass == ESocialClass::Noble) ? -0.03f : (SocialClass == ESocialClass::Cheonmin ? 0.05f : 0.f);
    const float RepModifier = FMath::GetMappedRangeValueClamped(FVector2D(-100.f, 100.f), FVector2D(0.05f, -0.03f), Reputation);
    return FMath::Clamp(Base + ClassModifier + RepModifier, 0.01f, 0.4f);
}

float AJoseonPlayerState::GetWantedGainMultiplier() const
{
    const float ClassScale = (SocialClass == ESocialClass::Noble) ? 0.7f : (SocialClass == ESocialClass::Outlaw ? 1.4f : 1.f);
    return FMath::Clamp(ClassScale + (-Reputation * 0.003f), 0.5f, 2.f);
}

float AJoseonPlayerState::GetShopPriceMultiplier() const
{
    const float ClassDiscount = (SocialClass == ESocialClass::Noble) ? -0.1f : (SocialClass == ESocialClass::Cheonmin ? 0.2f : 0.f);
    const float RepDiscount = FMath::GetMappedRangeValueClamped(FVector2D(-100.f, 100.f), FVector2D(0.2f, -0.15f), Reputation);
    return FMath::Clamp(1.f + ClassDiscount + RepDiscount, 0.5f, 2.5f);
}

int32 AJoseonPlayerState::GetDialogueAccessTier() const
{
    int32 Tier = 1;
    if (SocialClass == ESocialClass::Noble) Tier += 2;
    if (SocialClass == ESocialClass::Jungin) Tier += 1;
    Tier += Reputation >= 50.f ? 1 : (Reputation <= -50.f ? -1 : 0);
    return FMath::Clamp(Tier, 0, 4);
}

void AJoseonPlayerState::ServerSetSocialClass_Implementation(ESocialClass InClass)
{
    SocialClass = InClass;
    OnRep_SocialData();
}

void AJoseonPlayerState::ServerSetReputation_Implementation(float InValue)
{
    Reputation = FMath::Clamp(InValue, -100.f, 100.f);
    OnRep_SocialData();
}

void AJoseonPlayerState::ServerAddWantedHeat_Implementation(float DeltaHeat)
{
    WantedHeat = FMath::Clamp(WantedHeat + DeltaHeat * GetWantedGainMultiplier(), 0.f, 100.f);
    RecalculateWantedLevel();
    OnRep_WantedData();
}

void AJoseonPlayerState::ServerSetWantedHeat_Implementation(float InHeat)
{
    WantedHeat = FMath::Clamp(InHeat, 0.f, 100.f);
    RecalculateWantedLevel();
    OnRep_WantedData();
}

void AJoseonPlayerState::ServerSetFactionRep_Implementation(EFaction Faction, float NewRep)
{
    FactionReps.FindOrAdd(Faction) = FMath::Clamp(NewRep, -100.f, 100.f);
    OnFactionRepChanged.Broadcast(Faction, FactionReps[Faction]);
}

void AJoseonPlayerState::ServerAddFactionRep_Implementation(EFaction Faction, float Delta)
{
    const float Current = GetFactionRep(Faction);
    FactionReps.FindOrAdd(Faction) = FMath::Clamp(Current + Delta, -100.f, 100.f);
    OnFactionRepChanged.Broadcast(Faction, FactionReps[Faction]);
}

void AJoseonPlayerState::OnRep_SocialData()
{
    UE_LOG(LogJoseon, Log, TEXT("사회 데이터 갱신: Class=%d Reputation=%.2f"), (int32)SocialClass, Reputation);
    OnSocialClassChanged.Broadcast(SocialClass, Reputation);
}

void AJoseonPlayerState::OnRep_WantedData()
{
    UE_LOG(LogJoseon, Log, TEXT("수배 데이터 갱신: Level=%d Heat=%.2f"), WantedLevel, WantedHeat);
    OnWantedStateChanged.Broadcast(WantedLevel, WantedHeat);
}

void AJoseonPlayerState::RecalculateWantedLevel()
{
    static const TArray<float> Thresholds = {0.f, 20.f, 40.f, 60.f, 80.f, 95.f};
    int32 NewLevel = 0;
    for (int32 i = Thresholds.Num() - 1; i >= 0; --i)
    {
        if (WantedHeat >= Thresholds[i])
        {
            NewLevel = i;
            break;
        }
    }
    WantedLevel = FMath::Clamp(NewLevel, 0, 5);
}

void AJoseonPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AJoseonPlayerState, SocialClass);
    DOREPLIFETIME(AJoseonPlayerState, Reputation);
    DOREPLIFETIME(AJoseonPlayerState, WantedLevel);
    DOREPLIFETIME(AJoseonPlayerState, WantedHeat);
    DOREPLIFETIME(AJoseonPlayerState, FactionReps);
}
