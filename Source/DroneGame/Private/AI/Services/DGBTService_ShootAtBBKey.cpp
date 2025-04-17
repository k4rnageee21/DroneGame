#include "AI/Services/DGBTService_ShootAtBBKey.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/DGCombatComponent.h"
#include "Interfaces/DGCombatInterface.h"

UDGBTService_ShootAtBBKey::UDGBTService_ShootAtBBKey()
{
	NodeName = "Shoot At BB Key";
    bNotifyTick = true;
    bNotifyBecomeRelevant = true;
    bNotifyCeaseRelevant = true;
}

uint16 UDGBTService_ShootAtBBKey::GetInstanceMemorySize() const
{
	return sizeof(FDGBTService_ShootAtBBKeyMemory);
}

bool UDGBTService_ShootAtBBKey::IsMemoryNodeValid(uint8* NodeMemory) const
{
    FDGBTService_ShootAtBBKeyMemory* MyMemory = reinterpret_cast<FDGBTService_ShootAtBBKeyMemory*>(NodeMemory);
    return MyMemory->CombatComponent.IsValid() && MyMemory->TargetActor.IsValid();
}

void UDGBTService_ShootAtBBKey::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIC = OwnerComp.GetAIOwner();
    if (!IsValid(AIC))
    {
        return;
    }
    APawn* Pawn = AIC->GetPawn();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!IsValid(Blackboard) || !IsValid(Pawn))
    {
        return;
    }
    AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(BlackboardKey.SelectedKeyName));
    if (!IsValid(Target))
    {
        return;
    }
    IDGCombatInterface* CombatInterface = Cast<IDGCombatInterface>(Pawn);
    if (CombatInterface)
    {
        FDGBTService_ShootAtBBKeyMemory* MyMemory = reinterpret_cast<FDGBTService_ShootAtBBKeyMemory*>(NodeMemory);
        MyMemory->TargetActor = Target;
        MyMemory->CombatComponent = CombatInterface->GetCombatComponent();
    }
}

void UDGBTService_ShootAtBBKey::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (!IsMemoryNodeValid(NodeMemory))
    {
        return;
    }

    FDGBTService_ShootAtBBKeyMemory* MyMemory = reinterpret_cast<FDGBTService_ShootAtBBKeyMemory*>(NodeMemory);
    MyMemory->CombatComponent->Shoot(MyMemory->TargetActor->GetActorLocation());
}

void UDGBTService_ShootAtBBKey::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FDGBTService_ShootAtBBKeyMemory* MyMemory = reinterpret_cast<FDGBTService_ShootAtBBKeyMemory*>(NodeMemory);

	MyMemory->TargetActor.Reset();
	MyMemory->CombatComponent.Reset();
}
