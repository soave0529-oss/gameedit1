#include "Networking/JoseonNetworkBlueprintLibrary.h"
#include "Engine/World.h"

bool UJoseonNetworkBlueprintLibrary::IsServerAuthority(const UObject* WorldContextObject)
{
    const UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
    return World && World->GetNetMode() != NM_Client;
}
