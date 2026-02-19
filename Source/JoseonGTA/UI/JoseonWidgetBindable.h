#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JoseonWidgetBindable.generated.h"

class UJoseonHUDViewModel;

UINTERFACE(BlueprintType)
class JOSEONGTA_API UJoseonWidgetBindable : public UInterface
{
    GENERATED_BODY()
};

class JOSEONGTA_API IJoseonWidgetBindable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Joseon|UI")
    void BindViewModel(UJoseonHUDViewModel* ViewModel);
};
