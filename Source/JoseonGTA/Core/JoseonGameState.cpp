#include "Core/JoseonGameState.h"
#include "Net/UnrealNetwork.h"

AJoseonGameState::AJoseonGameState()
{
    bReplicates = true;
}

void AJoseonGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AJoseonGameState, GlobalCrimeIntensity);
}
