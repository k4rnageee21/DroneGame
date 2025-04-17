#include "Projectiles/DGProjectileBase.h"
#include "Components/BoxComponent.h"
#include "Components/DGHealthComponent.h"
#include "DroneGameTypes/CollisionChannels.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/DGDamageable.h"
#include "WorldSubsystems/DGObjectPoolSubsystem.h"

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

	ObjectPoolSubsystem = UWorld::GetSubsystem<UDGObjectPoolSubsystem>(GetWorld());
}

void ADGProjectileBase::OnGetFromPool()
{
	SetActorHiddenInGame(false);
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	Collision->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	RestoreMovement();
	GetWorldTimerManager().SetTimer(LifetimeTH, this, &ThisClass::OnLifetimeEnd, LifetimeDuration, false);
}

void ADGProjectileBase::OnReturnToPool()
{
	SetActorHiddenInGame(true);
	Collision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	Collision->OnComponentHit.RemoveDynamic(this, &ThisClass::OnHit);
	GetWorldTimerManager().ClearTimer(LifetimeTH);
}

void ADGProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDGDamageable* Damageable = Cast<IDGDamageable>(OtherActor);
	if (Damageable)
	{
		UDGHealthComponent* HealthComponent = Damageable->GetHealthComponent();
		if (IsValid(HealthComponent))
		{
			HealthComponent->TakeDamage(BaseDamage);
		}
	}

	OnLifetimeEnd();
}

void ADGProjectileBase::OnLifetimeEnd()
{
	if (IsValid(ObjectPoolSubsystem))
	{
		ObjectPoolSubsystem->ReturnToPool(this);
	}
	else
	{
		Destroy();
	}
}

void ADGProjectileBase::RestoreMovement()
{
	Movement->Activate(true);
	Movement->SetUpdatedComponent(Collision);
	Movement->Velocity = GetActorRotation().Vector() * Movement->InitialSpeed;
}
