#include "AI/DGTurretAIController.h"
#include "AI/DGBlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ADGTurretAIController::ADGTurretAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

void ADGTurretAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void ADGTurretAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	APawn* SensedPawn = Cast<APawn>(Actor);
	if (!IsValid(SensedPawn) || !IsValid(Blackboard))
	{
		return;
	}
	APlayerController* SensedPawnPC = SensedPawn->GetController<APlayerController>();
	if (!IsValid(SensedPawnPC))
	{
		return;
	}

	// Could also check for different senses types, but for now we use only Sight Sense

	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(DGBlackboardKeys::TargetActor, SensedPawn);
		SensedPawn->OnDestroyed.AddDynamic(this, &ThisClass::HandleTargetDestroyed);
	}
	else
	{
		SensedPawn->OnDestroyed.RemoveDynamic(this, &ThisClass::HandleTargetDestroyed);
		Blackboard->SetValueAsObject(DGBlackboardKeys::TargetActor, nullptr);
	}
}

void ADGTurretAIController::HandleTargetDestroyed(AActor* DestroyedActor)
{
	if (IsValid(Blackboard))
	{
		Blackboard->SetValueAsObject(DGBlackboardKeys::TargetActor, nullptr);
	}
}
