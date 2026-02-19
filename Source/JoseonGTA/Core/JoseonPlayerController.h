#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JoseonPlayerController.generated.h"

class UUserWidget;
class UJoseonHUDViewModel;

UCLASS()
class JOSEONGTA_API AJoseonPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AJoseonPlayerController();

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Joseon|UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;

    UFUNCTION(BlueprintCallable, Category="Joseon|UI")
    UJoseonHUDViewModel* GetHUDViewModel() const { return HUDViewModel; }

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Quest")
    void ServerAdvanceQuest(const FString& QuestId, const FString& StepId, int32 DeltaCount);

protected:
    UPROPERTY()
    TObjectPtr<UUserWidget> HUDWidget;

    UPROPERTY()
    TObjectPtr<UJoseonHUDViewModel> HUDViewModel;
};
