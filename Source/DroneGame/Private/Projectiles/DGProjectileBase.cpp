#include "Projectiles/DGProjectileBase.h"
#include "Components/BoxComponent.h"
#include "DroneGameTypes/CollisionChannels.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADGProjectileBase::ADGProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionObjectType(CollisionChannels::Projectile);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;
	Movement->ProjectileGravityScale = 0.f;
}

void ADGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}
