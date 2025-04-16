#include "Items/DGPickUpItemBase.h"
#include "Components/BoxComponent.h"
#include "DroneGameTypes/CollisionChannels.h"

ADGPickUpItemBase::ADGPickUpItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Mesh);
	Collision->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECollisionResponse::ECR_Ignore);
}

float ADGPickUpItemBase::CalculateAddedValue()
{
	MinValue = FMath::Min(MinValue, MaxValue);
	return bShouldAddFixedValue ? FixedValue : FMath::RandRange(MinValue, MaxValue);
}

void ADGPickUpItemBase::PickUp(APawn* PickingPawn)
{
	Destroy();
}
