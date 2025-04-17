#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "DGBTTask_RotateToBBKey.generated.h"

struct FDGBTTask_RotateToBBKeyMemory
{
	TWeakObjectPtr<AActor> TargetActor;
	TWeakObjectPtr<APawn> PawnToRotate;
};

/*
*	Similar task exists in the engine, but that task doesn't do what I want
*/
UCLASS()
class DRONEGAME_API UDGBTTask_RotateToBBKey : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UDGBTTask_RotateToBBKey();

	virtual uint16 GetInstanceMemorySize() const override;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	bool IsInAcceptableAngle(float CurrentYaw, float DesiredYaw) const;
	bool IsMemoryNodeValid(uint8* NodeMemory) const;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotationSpeed = 90.f; // degrees per second

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float AcceptableAngle = 5.f;
};
