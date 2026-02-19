#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/JoseonTypes.h"
#include "SocialClassComponent.generated.h"

class AJoseonPlayerState;

UCLASS(ClassGroup=(Joseon), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class JOSEONGTA_API USocialClassComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USocialClassComponent();

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    ESocialClass GetCachedSocialClass() const { return CachedSocialClass; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    float GetCachedReputation() const { return CachedReputation; }

    UFUNCTION(BlueprintCallable, Category="Joseon|Social")
    void SyncFromPlayerState();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(ReplicatedUsing=OnRep_CachedSocial, BlueprintReadOnly, Category="Joseon|Social")
    ESocialClass CachedSocialClass = ESocialClass::Sangmin;

    UPROPERTY(ReplicatedUsing=OnRep_CachedSocial, BlueprintReadOnly, Category="Joseon|Social")
    float CachedReputation = 0.f;

    UFUNCTION()
    void OnRep_CachedSocial();

    AJoseonPlayerState* ResolveJoseonPlayerState() const;

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
