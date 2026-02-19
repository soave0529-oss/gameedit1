#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetPatrolLocation.generated.h"

UCLASS()
class JOSEONGTA_API UBTTask_SetPatrolLocation : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_SetPatrolLocation();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
