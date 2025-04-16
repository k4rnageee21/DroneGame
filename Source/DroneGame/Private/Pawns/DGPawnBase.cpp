#include "Pawns/DGPawnBase.h"
#include "Components/BoxComponent.h"
#include "Components/DGHealthComponent.h"
#include "DroneGameTypes/CollisionChannels.h"

ADGPawnBase::ADGPawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECollisionResponse::ECR_Ignore);

	MainHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MainHitBox"));
	MainHitBox->SetupAttachment(RootComponent);
	MainHitBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	MainHitBox->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECollisionResponse::ECR_Block);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UDGHealthComponent>(TEXT("HealthComponent"));
}

void ADGPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(HealthComponent))
	{
		HealthComponent->OnDead.AddDynamic(this, &ThisClass::OnDeath);
	}
}

void ADGPawnBase::OnDeath()
{
	Destroy();
}
