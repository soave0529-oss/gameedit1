#include "Systems/JoseonSaveSubsystem.h"
#include "Core/JoseonPlayerState.h"
#include "Characters/JoseonCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Systems/JoseonSaveGame.h"
#include "Systems/QuestManager.h"

UJoseonSaveGame* UJoseonSaveSubsystem::GetOrCreateSaveObject()
{
    if (USaveGame* Existing = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0))
    {
        return Cast<UJoseonSaveGame>(Existing);
    }
    return Cast<UJoseonSaveGame>(UGameplayStatics::CreateSaveGameObject(UJoseonSaveGame::StaticClass()));
}

bool UJoseonSaveSubsystem::SaveCurrentState(AJoseonCharacterBase* Character)
{
    if (!Character)
    {
        return false;
    }

    UJoseonSaveGame* SaveObject = GetOrCreateSaveObject();
    AJoseonPlayerState* PS = Character->GetPlayerState<AJoseonPlayerState>();
    if (!SaveObject || !PS)
    {
        return false;
    }

    SaveObject->PlayerLocation = Character->GetActorLocation();
    SaveObject->PlayerRotation = Character->GetActorRotation();
    SaveObject->SocialClass = PS->GetSocialClass();
    SaveObject->Reputation = PS->GetReputation();
    SaveObject->WantedLevel = PS->GetWantedLevel();
    SaveObject->WantedHeat = PS->GetWantedHeat();

    SaveObject->FactionReps.Empty();
    SaveObject->FactionReps.Add(EFaction::Government, PS->GetFactionRep(EFaction::Government));
    SaveObject->FactionReps.Add(EFaction::MerchantGuild, PS->GetFactionRep(EFaction::MerchantGuild));
    SaveObject->FactionReps.Add(EFaction::Bandits, PS->GetFactionRep(EFaction::Bandits));
    SaveObject->FactionReps.Add(EFaction::SecretSociety, PS->GetFactionRep(EFaction::SecretSociety));

    if (UQuestManager* QuestManager = GetGameInstance()->GetSubsystem<UQuestManager>())
    {
        SaveObject->QuestStates = QuestManager->GetQuestStates();
    }

    return UGameplayStatics::SaveGameToSlot(SaveObject, SaveSlotName, 0);
}

bool UJoseonSaveSubsystem::LoadCurrentState(AJoseonCharacterBase* Character)
{
    if (!Character)
    {
        return false;
    }

    UJoseonSaveGame* SaveObject = Cast<UJoseonSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    AJoseonPlayerState* PS = Character->GetPlayerState<AJoseonPlayerState>();
    if (!SaveObject || !PS)
    {
        return false;
    }

    Character->SetActorLocationAndRotation(SaveObject->PlayerLocation, SaveObject->PlayerRotation);
    PS->ServerSetSocialClass(SaveObject->SocialClass);
    PS->ServerSetReputation(SaveObject->Reputation);
    PS->ServerSetWantedHeat(SaveObject->WantedHeat);

    for (const TPair<EFaction, float>& Pair : SaveObject->FactionReps)
    {
        PS->ServerSetFactionRep(Pair.Key, Pair.Value);
    }

    if (UQuestManager* QuestManager = GetGameInstance()->GetSubsystem<UQuestManager>())
    {
        QuestManager->SetQuestStates(SaveObject->QuestStates);
    }

    return true;
}
