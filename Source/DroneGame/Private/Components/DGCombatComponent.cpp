#include "Components/DGCombatComponent.h"
#include "Pawns/DGPawnBase.h"
#include "Projectiles/DGProjectileBase.h"
#include "WorldSubsystems/DGObjectPoolSubsystem.h"

UDGCombatComponent::UDGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
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

	ObjectPoolSubsystem = UWorld::GetSubsystem<UDGObjectPoolSubsystem>(GetWorld());
}

void UDGCombatComponent::Shoot(const FVector& Target)
{
	if (!ProjectileClass || !CanShoot(Target))
	{
		return;
	}

	UWorld* World = GetWorld();
	check(IsValid(World));
	const FVector Start = GetShootStartLocationFromOwner();
	const FRotator StartRotation = (Target - Start).Rotation();
	if (IsValid(ObjectPoolSubsystem))
	{
		AActor* SpawnedActor = ObjectPoolSubsystem->GetFromPool(ProjectileClass, Start, StartRotation);
		if (SpawnedActor)
		{
			SetAmmo(CurrentAmmo - 1);
		}
	}
}

bool UDGCombatComponent::CanShoot(const FVector& Target) const
{
	return CurrentAmmo > 0;
}

FVector UDGCombatComponent::GetShootStartLocationFromOwner() const
{
	ADGPawnBase* Pawn = GetOwningPawn<ADGPawnBase>();
	return IsValid(Pawn) ? Pawn->GetMuzzleLocation() : FVector{};
}

void UDGCombatComponent::AddAmmo(int32 AddedAmmo)
{
	AddedAmmo = FMath::Max(0, AddedAmmo);
	SetAmmo(CurrentAmmo + AddedAmmo);
}

void UDGCombatComponent::SetAmmo(int32 NewAmmo)
{
	CurrentAmmo = FMath::Max(0, NewAmmo);
	OnAmmoChanged.Broadcast(CurrentAmmo);
}
