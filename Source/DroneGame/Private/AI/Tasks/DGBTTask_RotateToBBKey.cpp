#include "AI/Tasks/DGBTTask_RotateToBBKey.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDGBTTask_RotateToBBKey::UDGBTTask_RotateToBBKey()
{
    INIT_TASK_NODE_NOTIFY_FLAGS();
	NodeName = "Rotate To BB Key";
}

uint16 UDGBTTask_RotateToBBKey::GetInstanceMemorySize() const
{
    return sizeof(FDGBTTask_RotateToBBKeyMemory);
}

EBTNodeResult::Type UDGBTTask_RotateToBBKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!IsValid(AIC))
    {
        return EBTNodeResult::Failed;
    }
    APawn* Pawn = AIC->GetPawn();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!IsValid(Blackboard) || !IsValid(Pawn))
    {
        return EBTNodeResult::Failed;
    }
    AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
    if (!IsValid(Target))
    {
        return EBTNodeResult::Failed;
    }

    const FVector ToTarget = Target->GetActorLocation() - Pawn->GetActorLocation();
    const float DesiredYaw = ToTarget.Rotation().Yaw;
    const float CurrentYaw = Pawn->GetActorRotation().Yaw;
    if (IsInAcceptableAngle(CurrentYaw, DesiredYaw))
    {
        return EBTNodeResult::Succeeded;
    }

    FDGBTTask_RotateToBBKeyMemory* MyMemory = reinterpret_cast<FDGBTTask_RotateToBBKeyMemory*>(NodeMemory);
    MyMemory->TargetActor = Target;
    MyMemory->PawnToRotate = Pawn;

    return EBTNodeResult::InProgress;
}

void UDGBTTask_RotateToBBKey::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (!IsMemoryNodeValid(NodeMemory))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FDGBTTask_RotateToBBKeyMemory* MyMemory = reinterpret_cast<FDGBTTask_RotateToBBKeyMemory*>(NodeMemory);
    APawn* Pawn = MyMemory->PawnToRotate.Get();
    AActor* Target = MyMemory->TargetActor.Get();

    const FVector ToTarget = Target->GetActorLocation() - Pawn->GetActorLocation();
    const float DesiredYaw = ToTarget.Rotation().Yaw;
    const float CurrentYaw = Pawn->GetActorRotation().Yaw;
    const float NewYaw = FMath::FixedTurn(CurrentYaw, DesiredYaw, RotationSpeed * DeltaSeconds);
    
    FRotator NewRotation = Pawn->GetActorRotation();
    NewRotation.Yaw = NewYaw;

    Pawn->SetActorRotation(NewRotation);

    if (IsInAcceptableAngle(NewYaw, DesiredYaw))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

void UDGBTTask_RotateToBBKey::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    FDGBTTask_RotateToBBKeyMemory* MyMemory = reinterpret_cast<FDGBTTask_RotateToBBKeyMemory*>(NodeMemory);
    MyMemory->PawnToRotate.Reset();
    MyMemory->TargetActor.Reset();
}

bool UDGBTTask_RotateToBBKey::IsInAcceptableAngle(float CurrentYaw, float DesiredYaw) const
{
    const float YawDiff = FMath::Abs(FRotator::NormalizeAxis(CurrentYaw - DesiredYaw));
    return YawDiff <= AcceptableAngle;
}

bool UDGBTTask_RotateToBBKey::IsMemoryNodeValid(uint8* NodeMemory) const
{
    FDGBTTask_RotateToBBKeyMemory* MyMemory = reinterpret_cast<FDGBTTask_RotateToBBKeyMemory*>(NodeMemory);
    return MyMemory->PawnToRotate.IsValid() && MyMemory->TargetActor.IsValid();
}
