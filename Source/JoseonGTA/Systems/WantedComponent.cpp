#include "Systems/WantedComponent.h"
#include "Core/JoseonPlayerState.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

UWantedComponent::UWantedComponent()
{
    SetIsReplicatedByDefault(true);
}

void UWantedComponent::BeginPlay()
{
    Super::BeginPlay();
    if (AJoseonPlayerState* PS = ResolveJoseonPlayerState())
    {
        CachedWantedLevel = PS->GetWantedLevel();
        CachedWantedHeat = PS->GetWantedHeat();
    }
}

void UWantedComponent::AddWantedHeat(float DeltaHeat)
{
    if (AJoseonPlayerState* PS = ResolveJoseonPlayerState())
    {
        PS->ServerAddWantedHeat(DeltaHeat);
        CachedWantedLevel = PS->GetWantedLevel();
        CachedWantedHeat = PS->GetWantedHeat();
        OnWantedChanged.Broadcast(CachedWantedLevel, CachedWantedHeat);
    }
}

void UWantedComponent::SetWantedHeat(float NewHeat)
{
    if (AJoseonPlayerState* PS = ResolveJoseonPlayerState())
    {
        PS->ServerSetWantedHeat(NewHeat);
        CachedWantedLevel = PS->GetWantedLevel();
        CachedWantedHeat = PS->GetWantedHeat();
        OnWantedChanged.Broadcast(CachedWantedLevel, CachedWantedHeat);
    }
}

void UWantedComponent::OnRep_CachedWanted()
{
    OnWantedChanged.Broadcast(CachedWantedLevel, CachedWantedHeat);
}

AJoseonPlayerState* UWantedComponent::ResolveJoseonPlayerState() const
{
    const APawn* PawnOwner = Cast<APawn>(GetOwner());
    if (!PawnOwner)
    {
        return nullptr;
    }
    return PawnOwner->GetPlayerState<AJoseonPlayerState>();
}

void UWantedComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UWantedComponent, CachedWantedLevel);
    DOREPLIFETIME(UWantedComponent, CachedWantedHeat);
}
