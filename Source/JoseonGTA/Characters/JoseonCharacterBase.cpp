#include "Characters/JoseonCharacterBase.h"
#include "Systems/SocialClassComponent.h"
#include "Systems/WantedComponent.h"
#include "Systems/CombatComponent.h"

AJoseonCharacterBase::AJoseonCharacterBase()
{
    bReplicates = true;

    SocialClassComponent = CreateDefaultSubobject<USocialClassComponent>(TEXT("SocialClassComponent"));
    WantedComponent = CreateDefaultSubobject<UWantedComponent>(TEXT("WantedComponent"));
    CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void AJoseonCharacterBase::BeginPlay()
{
    Super::BeginPlay();
}

void AJoseonCharacterBase::ServerAttack_Implementation(bool bHeavy)
{
    if (!CombatComponent)
    {
        return;
    }

    if (bHeavy)
    {
        CombatComponent->AttackHeavy();
    }
    else
    {
        CombatComponent->AttackLight();
    }
}

void AJoseonCharacterBase::AddCrimeHeat(float Delta)
{
    if (WantedComponent)
    {
        WantedComponent->AddWantedHeat(Delta);
    }
}
