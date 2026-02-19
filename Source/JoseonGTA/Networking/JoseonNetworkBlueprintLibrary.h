#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JoseonNetworkBlueprintLibrary.generated.h"

UCLASS()
class JOSEONGTA_API UJoseonNetworkBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="Joseon|Network")
    static bool IsServerAuthority(const UObject* WorldContextObject);
};
