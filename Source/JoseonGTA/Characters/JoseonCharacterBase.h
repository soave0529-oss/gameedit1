#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/CombatantInterface.h"
#include "Core/JoseonTypes.h"
#include "JoseonCharacterBase.generated.h"

class USocialClassComponent;
class UWantedComponent;
class UCombatComponent;

UCLASS(Blueprintable)
class JOSEONGTA_API AJoseonCharacterBase : public ACharacter, public ICombatantInterface
{
    GENERATED_BODY()

public:
    AJoseonCharacterBase();

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Joseon|Components")
    TObjectPtr<USocialClassComponent> SocialClassComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Joseon|Components")
    TObjectPtr<UWantedComponent> WantedComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Joseon|Components")
    TObjectPtr<UCombatComponent> CombatComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Stats")
    float Strength = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joseon|Stats")
    float Dexterity = 10.f;

    virtual float GetStrength_Implementation() const override { return Strength; }
    virtual float GetDexterity_Implementation() const override { return Dexterity; }

    UFUNCTION(Server, Reliable, BlueprintCallable, Category="Joseon|Combat")
    void ServerAttack(bool bHeavy);

    UFUNCTION(BlueprintCallable, Category="Joseon|Wanted")
    void AddCrimeHeat(float Delta);
};
