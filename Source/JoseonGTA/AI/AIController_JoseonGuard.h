#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AIController_JoseonGuard.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UBlackboardComponent;

UCLASS()
class JOSEONGTA_API AAIController_JoseonGuard : public AAIController
{
    GENERATED_BODY()

public:
    AAIController_JoseonGuard();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Joseon|AI")
    TObjectPtr<UAIPerceptionComponent> PerceptionComponent;

    UPROPERTY()
    TObjectPtr<UAISenseConfig_Sight> SightConfig;

    UPROPERTY()
    TObjectPtr<UAISenseConfig_Hearing> HearingConfig;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Joseon|AI")
    TObjectPtr<UBlackboardComponent> GuardBlackboard;

    UPROPERTY(EditDefaultsOnly, Category="Joseon|AI")
    float LoseTargetSeconds = 6.f;

    UPROPERTY(BlueprintReadOnly, Category="Joseon|AI")
    FVector LastKnownTargetLocation = FVector::ZeroVector;

    UPROPERTY(BlueprintReadOnly, Category="Joseon|AI")
    float LostSightTime = 0.f;

    UPROPERTY(BlueprintReadOnly, Category="Joseon|AI")
    bool bHasTarget = false;

    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    void EnterPursuit(AActor* TargetActor, const FVector& SensedLocation);
    void EnterSearch();
    void EnterPatrol();
};
