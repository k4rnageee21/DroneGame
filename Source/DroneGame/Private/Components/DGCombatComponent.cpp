#include "Components/DGCombatComponent.h"
#include "Projectiles/DGProjectileBase.h"

UDGCombatComponent::UDGCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UDGCombatComponent::Shoot(const FVector& Start, const FVector& LookAtVector)
{
	if (!ProjectileClass)
	{
		return;
	}

	UWorld* World = GetWorld();
	check(IsValid(World));
	const FRotator StartRotation = LookAtVector.Rotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetOwner<APawn>();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	World->SpawnActor(ProjectileClass, &Start, &StartRotation, SpawnParams);
}

void UDGCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}
