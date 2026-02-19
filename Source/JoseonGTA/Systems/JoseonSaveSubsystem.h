#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JoseonSaveSubsystem.generated.h"

class UJoseonSaveGame;
class AJoseonCharacterBase;

UCLASS()
class JOSEONGTA_API UJoseonSaveSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Save")
    FString SaveSlotName = TEXT("joseon_slot_0");

    UFUNCTION(BlueprintCallable, Category="Joseon|Save")
    bool SaveCurrentState(AJoseonCharacterBase* Character);

    UFUNCTION(BlueprintCallable, Category="Joseon|Save")
    bool LoadCurrentState(AJoseonCharacterBase* Character);

    UFUNCTION(BlueprintCallable, Category="Joseon|Save")
    UJoseonSaveGame* GetOrCreateSaveObject();
};
