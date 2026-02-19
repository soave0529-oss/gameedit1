#include "AI/BTTask_SetPatrolLocation.h"
#include "AIController.h"
#include "AI/JoseonAIKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetPatrolLocation::UBTTask_SetPatrolLocation()
{
    NodeName = TEXT("순찰 위치 갱신");
}

EBTNodeResult::Type UBTTask_SetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    APawn* Pawn = Controller ? Controller->GetPawn() : nullptr;
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    const FVector PatrolLocation = Pawn->GetActorLocation() + FMath::VRand() * 800.f;
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(JoseonAIKeys::PatrolLocation, PatrolLocation);
    return EBTNodeResult::Succeeded;
}
