#include "Core/JoseonGameModeBase.h"
#include "Characters/JoseonCharacterBase.h"
#include "Core/JoseonPlayerController.h"
#include "Core/JoseonPlayerState.h"
#include "Core/JoseonGameState.h"

AJoseonGameModeBase::AJoseonGameModeBase()
{
    DefaultPawnClass = AJoseonCharacterBase::StaticClass();
    PlayerControllerClass = AJoseonPlayerController::StaticClass();
    PlayerStateClass = AJoseonPlayerState::StaticClass();
    GameStateClass = AJoseonGameState::StaticClass();
}
