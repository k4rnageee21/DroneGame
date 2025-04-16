#include "Pawns/DGTurret.h"
#include "Components/DGTurretCombatComponent.h"

ADGTurret::ADGTurret()
{
	CombatComponent = CreateDefaultSubobject<UDGTurretCombatComponent>(TEXT("CombatComponent"));
}
