#include "Items/DGPickUpAmmo.h"
#include "Components/DGCombatComponent.h"
#include "Interfaces/DGCombatInterface.h"

void ADGPickUpAmmo::PickUp(APawn* PickingPawn)
{
	IDGCombatInterface* CombatInterface = Cast<IDGCombatInterface>(PickingPawn);
	if (CombatInterface)
	{
		UDGCombatComponent* CombatComponent = CombatInterface->GetCombatComponent();
		if (IsValid(CombatComponent))
		{
			int32 AddedAmmo = FMath::RoundToInt(CalculateAddedValue());
			CombatComponent->AddAmmo(AddedAmmo);
		}
	}

	Super::PickUp(PickingPawn);
}
