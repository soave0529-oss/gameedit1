#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Core/JoseonTypes.h"
#include "FactionSubsystem.generated.h"

UCLASS()
class JOSEONGTA_API UFactionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Joseon|Faction")
    float GetFactionRep(EFaction Faction) const;

    UFUNCTION(BlueprintCallable, Category="Joseon|Faction")
    void SetFactionRep(EFaction Faction, float NewValue);

    UFUNCTION(BlueprintCallable, Category="Joseon|Faction")
    void AddFactionRep(EFaction Faction, float Delta);

    UFUNCTION(BlueprintCallable, Category="Joseon|Faction")
    bool GetHostilityLevel(EFaction Faction) const;

private:
    UPROPERTY()
    TMap<EFaction, float> GlobalFactionRep;
};
