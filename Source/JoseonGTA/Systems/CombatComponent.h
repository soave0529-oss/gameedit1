#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/JoseonTypes.h"
#include "CombatComponent.generated.h"

UCLASS(ClassGroup=(Joseon), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class JOSEONGTA_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatComponent();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void AttackLight();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void AttackHeavy();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void BlockStart();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void BlockStop();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void Fire();

    UFUNCTION(BlueprintCallable, Category="Joseon|Combat")
    void Reload();

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Combat")
    void ServerAttack(bool bHeavy);

    UFUNCTION(NetMulticast, Unreliable)
    void MulticastPlayAttackFX(EWeaponType WeaponType, bool bHeavy);

protected:
    UPROPERTY(ReplicatedUsing=OnRep_CurrentWeaponType, EditAnywhere, BlueprintReadOnly, Category="Joseon|Combat")
    EWeaponType CurrentWeaponType = EWeaponType::Sword;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Joseon|Combat")
    float ReloadTime = 1.5f;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Joseon|Combat")
    int32 Ammo = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Joseon|Combat")
    int32 MaxAmmo = 10;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Joseon|Combat")
    int32 ComboIndex = 0;

    UPROPERTY(Replicated, BlueprintReadOnly, Category="Joseon|Combat")
    float ComboWindowTimer = 0.f;

    UPROPERTY(Replicated)
    bool bIsBlocking = false;

    UFUNCTION()
    void OnRep_CurrentWeaponType();

    float ComputeDamage(bool bHeavy) const;
    float ComputeDefenseChance() const;
    void PerformMeleeTrace(float Damage);
    void PerformRangedTrace(float Damage);

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
