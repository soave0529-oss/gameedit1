#include "AI/AIController_JoseonGuard.h"
#include "AI/JoseonAIKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AAIController_JoseonGuard::AAIController_JoseonGuard()
{
    PrimaryActorTick.bCanEverTick = true;

    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
    SetPerceptionComponent(*PerceptionComponent);

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 2000.f;
    SightConfig->LoseSightRadius = 2400.f;
    SightConfig->PeripheralVisionAngleDegrees = 70.f;
    SightConfig->SetMaxAge(3.f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
    HearingConfig->HearingRange = 1600.f;
    HearingConfig->SetMaxAge(2.5f);
    HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
    HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
    HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

    PerceptionComponent->ConfigureSense(*SightConfig);
    PerceptionComponent->ConfigureSense(*HearingConfig);
    PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

    GuardBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("GuardBlackboard"));
}

void AAIController_JoseonGuard::BeginPlay()
{
    Super::BeginPlay();

    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_JoseonGuard::OnTargetPerceptionUpdated);
    if (GuardBlackboard)
    {
        GuardBlackboard->SetValueAsBool(JoseonAIKeys::bHasVisual, false);
        GuardBlackboard->SetValueAsVector(JoseonAIKeys::PatrolLocation, GetPawn() ? GetPawn()->GetActorLocation() : FVector::ZeroVector);
    }
}

void AAIController_JoseonGuard::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bHasTarget)
    {
        LostSightTime += DeltaSeconds;
        if (LostSightTime > LoseTargetSeconds)
        {
            EnterSearch();
        }
    }
}

void AAIController_JoseonGuard::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (!Actor)
    {
        return;
    }

    if (Stimulus.WasSuccessfullySensed())
    {
        EnterPursuit(Actor, Stimulus.StimulusLocation);
    }
    else
    {
        LastKnownTargetLocation = Stimulus.StimulusLocation;
    }
}

void AAIController_JoseonGuard::EnterPursuit(AActor* TargetActor, const FVector& SensedLocation)
{
    bHasTarget = true;
    LostSightTime = 0.f;
    LastKnownTargetLocation = SensedLocation;

    if (GuardBlackboard)
    {
        GuardBlackboard->SetValueAsObject(JoseonAIKeys::TargetActor, TargetActor);
        GuardBlackboard->SetValueAsVector(JoseonAIKeys::LastKnownLocation, SensedLocation);
        GuardBlackboard->SetValueAsBool(JoseonAIKeys::bHasVisual, true);
    }

    MoveToActor(TargetActor, 130.f, true, true, false, 0, true);
}

void AAIController_JoseonGuard::EnterSearch()
{
    bHasTarget = false;

    if (GuardBlackboard)
    {
        GuardBlackboard->SetValueAsBool(JoseonAIKeys::bHasVisual, false);
        GuardBlackboard->SetValueAsVector(JoseonAIKeys::LastKnownLocation, LastKnownTargetLocation);
    }

    MoveToLocation(LastKnownTargetLocation, 120.f, true, true, false, true, 0, true);
    EnterPatrol();
}

void AAIController_JoseonGuard::EnterPatrol()
{
    if (!GetPawn())
    {
        return;
    }

    const FVector Origin = GetPawn()->GetActorLocation();
    const FVector RandomPatrol = Origin + FMath::VRand() * 600.f;
    if (GuardBlackboard)
    {
        GuardBlackboard->SetValueAsVector(JoseonAIKeys::PatrolLocation, RandomPatrol);
    }
    MoveToLocation(RandomPatrol, 80.f, true, true, false, true, 0, true);
}
