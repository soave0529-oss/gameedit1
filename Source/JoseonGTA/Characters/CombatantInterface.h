#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatantInterface.generated.h"

UINTERFACE(BlueprintType)
class JOSEONGTA_API UCombatantInterface : public UInterface
{
    GENERATED_BODY()
};

class JOSEONGTA_API ICombatantInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Joseon|Combat")
    float GetStrength() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Joseon|Combat")
    float GetDexterity() const;
};
