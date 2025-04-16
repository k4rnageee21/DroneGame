#include "Pawns/DGPawnBase.h"
#include "Components/DGHealthComponent.h"

ADGPawnBase::ADGPawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UDGHealthComponent>(TEXT("HealthComponent"));
}

void ADGPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}
