#include "Pawns/DGPawnBase.h"
#include "Components/DGCombatComponent.h"
#include "Components/DGHealthComponent.h"

ADGPawnBase::ADGPawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UDGHealthComponent>(TEXT("HealthComponent"));
	CombatComponent = CreateDefaultSubobject<UDGCombatComponent>(TEXT("CombatComponent"));
}

void ADGPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}
