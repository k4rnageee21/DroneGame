#include "Items/DGPickUpHealth.h"
#include "Components/DGHealthComponent.h"
#include "Interfaces/DGDamageable.h"

void ADGPickUpHealth::PickUp(APawn* PickingPawn)
{
	IDGDamageable* Damageable = Cast<IDGDamageable>(PickingPawn);
	if (Damageable)
	{
		UDGHealthComponent* HealthComponent = Damageable->GetHealthComponent();
		if (IsValid(HealthComponent))
		{
			float AddedHealth = FMath::FloorToFloat(CalculateAddedValue());
			HealthComponent->Heal(AddedHealth);
		}
	}

	Super::PickUp(PickingPawn);
}
