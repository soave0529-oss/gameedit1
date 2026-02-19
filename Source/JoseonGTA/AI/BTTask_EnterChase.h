#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnterChase.generated.h"

UCLASS()
class JOSEONGTA_API UBTTask_EnterChase : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_EnterChase();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
