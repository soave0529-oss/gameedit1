#include "UI/JoseonHUDViewModel.h"
#include "Core/JoseonPlayerState.h"

void UJoseonHUDViewModel::InitializeFromPlayerState(AJoseonPlayerState* InPlayerState)
{
    BoundPlayerState = InPlayerState;
    if (!BoundPlayerState)
    {
        return;
    }

    BoundPlayerState->OnWantedStateChanged.AddDynamic(this, &UJoseonHUDViewModel::HandleWantedChanged);
    BoundPlayerState->OnSocialClassChanged.AddDynamic(this, &UJoseonHUDViewModel::HandleSocialChanged);
    BoundPlayerState->OnFactionRepChanged.AddDynamic(this, &UJoseonHUDViewModel::HandleFactionChanged);

    HandleWantedChanged(BoundPlayerState->GetWantedLevel(), BoundPlayerState->GetWantedHeat());
    HandleSocialChanged(BoundPlayerState->GetSocialClass(), BoundPlayerState->GetReputation());
}

void UJoseonHUDViewModel::HandleWantedChanged(int32 NewLevel, float NewHeat)
{
    OnWantedChanged.Broadcast(NewLevel, NewHeat);
}

void UJoseonHUDViewModel::HandleSocialChanged(ESocialClass NewClass, float NewReputation)
{
    OnReputationChanged.Broadcast(NewReputation);
}

void UJoseonHUDViewModel::HandleFactionChanged(EFaction Faction, float Value)
{
    OnFactionChanged.Broadcast(Faction, Value);
}
