#include "Core/JoseonPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/JoseonHUDViewModel.h"
#include "Core/JoseonPlayerState.h"
#include "Systems/QuestManager.h"

AJoseonPlayerController::AJoseonPlayerController()
{
    bReplicates = true;
}

void AJoseonPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDViewModel = NewObject<UJoseonHUDViewModel>(this);
    if (AJoseonPlayerState* JoseonPS = GetPlayerState<AJoseonPlayerState>())
    {
        HUDViewModel->InitializeFromPlayerState(JoseonPS);
    }

    if (IsLocalController() && HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
        }
    }
}

void AJoseonPlayerController::ServerAdvanceQuest_Implementation(const FString& QuestId, const FString& StepId, int32 DeltaCount)
{
    if (UQuestManager* QuestManager = GetGameInstance()->GetSubsystem<UQuestManager>())
    {
        QuestManager->AdvanceStep(QuestId, StepId, DeltaCount);
    }
}
