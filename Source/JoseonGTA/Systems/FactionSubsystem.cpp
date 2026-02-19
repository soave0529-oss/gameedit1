#include "Systems/FactionSubsystem.h"

float UFactionSubsystem::GetFactionRep(EFaction Faction) const
{
    if (const float* Found = GlobalFactionRep.Find(Faction))
    {
        return *Found;
    }
    return 0.f;
}

void UFactionSubsystem::SetFactionRep(EFaction Faction, float NewValue)
{
    GlobalFactionRep.FindOrAdd(Faction) = FMath::Clamp(NewValue, -100.f, 100.f);
}

void UFactionSubsystem::AddFactionRep(EFaction Faction, float Delta)
{
    const float Current = GetFactionRep(Faction);
    SetFactionRep(Faction, Current + Delta);
}

bool UFactionSubsystem::GetHostilityLevel(EFaction Faction) const
{
    return GetFactionRep(Faction) <= -50.f;
}
