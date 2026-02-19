#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JoseonGameState.generated.h"

UCLASS()
class JOSEONGTA_API AJoseonGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AJoseonGameState();

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Joseon|World")
    float GlobalCrimeIntensity = 0.0f;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
