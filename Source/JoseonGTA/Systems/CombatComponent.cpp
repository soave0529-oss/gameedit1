#include "Systems/CombatComponent.h"
#include "JoseonGTA.h"
#include "Characters/CombatantInterface.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UCombatComponent::UCombatComponent()
{
    SetIsReplicatedByDefault(true);
}

void UCombatComponent::AttackLight()
{
    ServerAttack(false);
}

void UCombatComponent::AttackHeavy()
{
    ServerAttack(true);
}

void UCombatComponent::BlockStart()
{
    bIsBlocking = true;
}

void UCombatComponent::BlockStop()
{
    bIsBlocking = false;
}

void UCombatComponent::Fire()
{
    if (CurrentWeaponType == EWeaponType::Bow || CurrentWeaponType == EWeaponType::Matchlock)
    {
        ServerAttack(false);
    }
}

void UCombatComponent::Reload()
{
    Ammo = MaxAmmo;
}

void UCombatComponent::ServerAttack_Implementation(bool bHeavy)
{
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
    {
        return;
    }

    const float Damage = ComputeDamage(bHeavy);
    if (CurrentWeaponType == EWeaponType::Bow || CurrentWeaponType == EWeaponType::Matchlock)
    {
        if (Ammo <= 0)
        {
            UE_LOG(LogJoseon, Warning, TEXT("탄약 부족으로 발사 실패"));
            return;
        }
        Ammo -= 1;
        PerformRangedTrace(Damage);
    }
    else
    {
        ComboIndex = (ComboIndex + 1) % 3;
        ComboWindowTimer = 0.8f;
        PerformMeleeTrace(Damage);
    }

    MulticastPlayAttackFX(CurrentWeaponType, bHeavy);
}

void UCombatComponent::MulticastPlayAttackFX_Implementation(EWeaponType WeaponType, bool bHeavy)
{
    UE_LOG(LogJoseon, Log, TEXT("공격 FX 재생: Weapon=%d Heavy=%d"), (int32)WeaponType, bHeavy ? 1 : 0);
}

void UCombatComponent::OnRep_CurrentWeaponType()
{
}

float UCombatComponent::ComputeDamage(bool bHeavy) const
{
    const AActor* OwnerActor = GetOwner();
    const ICombatantInterface* Combatant = Cast<ICombatantInterface>(OwnerActor);
    const float Strength = Combatant ? ICombatantInterface::Execute_GetStrength(OwnerActor) : 10.f;
    const float Dexterity = Combatant ? ICombatantInterface::Execute_GetDexterity(OwnerActor) : 10.f;

    float WeaponScale = 1.0f;
    switch (CurrentWeaponType)
    {
        case EWeaponType::Sword: WeaponScale = 1.1f; break;
        case EWeaponType::Bow: WeaponScale = 1.0f; break;
        case EWeaponType::Matchlock: WeaponScale = 1.6f; break;
        case EWeaponType::Spear: WeaponScale = 1.2f; break;
        default: break;
    }

    const float StatPart = Strength * 1.4f + Dexterity * 0.9f;
    return (bHeavy ? 30.f : 18.f) + StatPart * WeaponScale;
}

float UCombatComponent::ComputeDefenseChance() const
{
    const AActor* OwnerActor = GetOwner();
    const ICombatantInterface* Combatant = Cast<ICombatantInterface>(OwnerActor);
    const float Dex = Combatant ? ICombatantInterface::Execute_GetDexterity(OwnerActor) : 10.f;
    const float Base = FMath::Clamp(Dex * 0.02f, 0.05f, 0.45f);
    return bIsBlocking ? FMath::Clamp(Base + 0.35f, 0.f, 0.9f) : Base;
}

void UCombatComponent::PerformMeleeTrace(float Damage)
{
    AActor* OwnerActor = GetOwner();
    UWorld* World = GetWorld();
    if (!OwnerActor || !World)
    {
        return;
    }

    const FVector Start = OwnerActor->GetActorLocation();
    const FVector End = Start + OwnerActor->GetActorForwardVector() * 220.f;
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(JoseonMelee), false, OwnerActor);
    const bool bHit = World->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(80.f), Params);

    if (bHit && Hit.GetActor())
    {
        UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, nullptr, OwnerActor, nullptr);
    }
}

void UCombatComponent::PerformRangedTrace(float Damage)
{
    AActor* OwnerActor = GetOwner();
    UWorld* World = GetWorld();
    if (!OwnerActor || !World)
    {
        return;
    }

    const FVector Start = OwnerActor->GetActorLocation() + FVector(0.f, 0.f, 50.f);
    const FVector End = Start + OwnerActor->GetActorForwardVector() * 3000.f;
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(JoseonRanged), false, OwnerActor);
    if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params) && Hit.GetActor())
    {
        UGameplayStatics::ApplyDamage(Hit.GetActor(), Damage, nullptr, OwnerActor, nullptr);
    }
}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCombatComponent, CurrentWeaponType);
    DOREPLIFETIME(UCombatComponent, Ammo);
    DOREPLIFETIME(UCombatComponent, ComboIndex);
    DOREPLIFETIME(UCombatComponent, ComboWindowTimer);
    DOREPLIFETIME(UCombatComponent, bIsBlocking);
}
