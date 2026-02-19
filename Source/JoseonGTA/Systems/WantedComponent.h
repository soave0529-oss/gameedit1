#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WantedComponent.generated.h"

class AJoseonPlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWantedChangedSignature, int32, WantedLevel, float, WantedHeat);

UCLASS(ClassGroup=(Joseon), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class JOSEONGTA_API UWantedComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWantedComponent();

    UPROPERTY(BlueprintAssignable, Category="Joseon|Wanted")
    FWantedChangedSignature OnWantedChanged;

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    void AddWantedHeat(float DeltaHeat);

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    void SetWantedHeat(float NewHeat);

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    int32 GetWantedLevel() const { return CachedWantedLevel; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(ReplicatedUsing=OnRep_CachedWanted)
    int32 CachedWantedLevel = 0;

    UPROPERTY(ReplicatedUsing=OnRep_CachedWanted)
    float CachedWantedHeat = 0.f;

    UFUNCTION()
    void OnRep_CachedWanted();

    AJoseonPlayerState* ResolveJoseonPlayerState() const;

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
