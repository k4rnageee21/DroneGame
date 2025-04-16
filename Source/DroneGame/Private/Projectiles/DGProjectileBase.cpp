#include "Projectiles/DGProjectileBase.h"
#include "Components/BoxComponent.h"
#include "Components/DGHealthComponent.h"
#include "DroneGameTypes/CollisionChannels.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/DGDamageable.h"

ADGProjectileBase::ADGProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionObjectType(CollisionChannels::Projectile);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	Mesh->SetCastShadow(false);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 6000.f;
	Movement->MaxSpeed = 6000.f;
	Movement->bRotationFollowsVelocity = false;
	Movement->bShouldBounce = false;
	Movement->ProjectileGravityScale = 0.f;
}

void ADGProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	GetWorldTimerManager().SetTimer(LifetimeTH, this, &ThisClass::OnLifetimeEnd, LifetimeDuration, false);
}

void ADGProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDGDamageable* Damageable = Cast<IDGDamageable>(OtherActor);
	if (!Damageable)
	{
		LifetimeTH.Invalidate(); // TODO: Remove this if I wouldn't be able to make object pool in time
		Destroy();
		return;
	}

	UDGHealthComponent* HealthComponent = Damageable->GetHealthComponent();
	if (IsValid(HealthComponent))
	{
		HealthComponent->TakeDamage(BaseDamage);
		LifetimeTH.Invalidate(); // TODO: Remove this if I wouldn't be able to make object pool in time
		Destroy();
	}
}

void ADGProjectileBase::OnLifetimeEnd()
{
	LifetimeTH.Invalidate(); // TODO: Remove this if I wouldn't be able to make object pool in time
	Destroy();
}
