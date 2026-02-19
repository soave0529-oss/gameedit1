#pragma once

#include "CoreMinimal.h"
#include "JoseonTypes.generated.h"

UENUM(BlueprintType)
enum class ESocialClass : uint8
{
    Noble UMETA(DisplayName = "양반"),
    Jungin UMETA(DisplayName = "중인"),
    Sangmin UMETA(DisplayName = "상민"),
    Cheonmin UMETA(DisplayName = "천민"),
    Outlaw UMETA(DisplayName = "무뢰배")
};

UENUM(BlueprintType)
enum class EFaction : uint8
{
    Government UMETA(DisplayName = "관군"),
    MerchantGuild UMETA(DisplayName = "상단"),
    Bandits UMETA(DisplayName = "도적"),
    SecretSociety UMETA(DisplayName = "비밀결사")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    Sword,
    Bow,
    Matchlock,
    Spear
};

UENUM(BlueprintType)
enum class EQuestStepType : uint8
{
    Kill,
    Deliver,
    Reach,
    Steal,
    Escort
};

UENUM(BlueprintType)
enum class EQuestState : uint8
{
    NotStarted,
    InProgress,
    Completed,
    Failed
};
