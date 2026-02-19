#include "AI/BTTask_EnterChase.h"
#include "AIController.h"
#include "AI/JoseonAIKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_EnterChase::UBTTask_EnterChase()
{
    NodeName = TEXT("추적 이동 시작");
}

EBTNodeResult::Type UBTTask_EnterChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* Controller = OwnerComp.GetAIOwner();
    UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(JoseonAIKeys::TargetActor);
    AActor* TargetActor = Cast<AActor>(Target);
    if (!Controller || !TargetActor)
    {
        return EBTNodeResult::Failed;
    }

    Controller->MoveToActor(TargetActor, 150.f, true, true, false, 0, true);
    return EBTNodeResult::Succeeded;
}
