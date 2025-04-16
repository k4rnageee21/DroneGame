#include "Components/DGCombatComponent.h"
#include "Projectiles/DGProjectileBase.h"

UDGCombatComponent::UDGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UDGCombatComponent::Shoot(const FVector& Start, const FVector& Target)
{
	if (!ProjectileClass || !CanShoot(Target))
	{
		return;
	}

	UWorld* World = GetWorld();
	check(IsValid(World));
	const FRotator StartRotation = (Target - Start).Rotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetOwner<APawn>();

	AActor* SpawnedActor = World->SpawnActor(ProjectileClass, &Start, &StartRotation, SpawnParams);
	if (SpawnedActor)
	{
		CurrentAmmo--;
	}
}

void UDGCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void UDGCombatComponent::Init()
{
	StartAmmo = FMath::Min(StartAmmo, MaxAmmo);
	CurrentAmmo = StartAmmo;
}

bool UDGCombatComponent::CanShoot(const FVector& Target) const
{
	return CurrentAmmo > 0;
}
