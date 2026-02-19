#include "Systems/SocialClassComponent.h"
#include "Core/JoseonPlayerState.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"

USocialClassComponent::USocialClassComponent()
{
    SetIsReplicatedByDefault(true);
}

void USocialClassComponent::BeginPlay()
{
    Super::BeginPlay();
    SyncFromPlayerState();
}

void USocialClassComponent::SyncFromPlayerState()
{
    if (AJoseonPlayerState* PS = ResolveJoseonPlayerState())
    {
        CachedSocialClass = PS->GetSocialClass();
        CachedReputation = PS->GetReputation();
    }
}

void USocialClassComponent::OnRep_CachedSocial()
{
}

AJoseonPlayerState* USocialClassComponent::ResolveJoseonPlayerState() const
{
    const APawn* PawnOwner = Cast<APawn>(GetOwner());
    if (!PawnOwner)
    {
        return nullptr;
    }
    return PawnOwner->GetPlayerState<AJoseonPlayerState>();
}

void USocialClassComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(USocialClassComponent, CachedSocialClass);
    DOREPLIFETIME(USocialClassComponent, CachedReputation);
}
