#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "DGBTService_ShootAtBBKey.generated.h"

class UDGCombatComponent;

struct FDGBTService_ShootAtBBKeyMemory
{
	TWeakObjectPtr<AActor> TargetActor;
	TWeakObjectPtr<UDGCombatComponent> CombatComponent;
};

UCLASS()
class DRONEGAME_API UDGBTService_ShootAtBBKey : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UDGBTService_ShootAtBBKey();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;

	bool IsMemoryNodeValid(uint8* NodeMemory) const;
};
