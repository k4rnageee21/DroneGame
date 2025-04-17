#include "WorldSubsystems/DGObjectPoolSubsystem.h"
#include "Interfaces/DGPoolable.h"

AActor* UDGObjectPoolSubsystem::GetFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation)
{
	AActor* PooledActor = nullptr;

	if (!PoolClass.Get()->ImplementsInterface(UDGPoolable::StaticClass()))
	{
		return PooledActor;
	}

	FPoolArray& ObjectPool = ObjectPools.FindOrAdd(PoolClass);
	if (ObjectPool.IsEmpty())
	{
		UWorld* World = GetWorld();
		check(IsValid(World));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		PooledActor = World->SpawnActor<AActor>(PoolClass, Location, Rotation, SpawnParams);
	}
	else
	{
		PooledActor = ObjectPool.Pop();
		if (IsValid(PooledActor))
		{
			PooledActor->SetActorLocationAndRotation(Location, Rotation);
		}
	}

	IDGPoolable* PoolableInterface = Cast<IDGPoolable>(PooledActor);
	if (PoolableInterface)
	{
		PoolableInterface->OnGetFromPool();
	}

	return PooledActor;
}

void UDGObjectPoolSubsystem::ReturnToPool(AActor* Actor)
{
	IDGPoolable* PoolableInterface = Cast<IDGPoolable>(Actor);
	if (PoolableInterface)
	{
		PoolableInterface->OnReturnToPool();
		FPoolArray* ObjectPool = ObjectPools.Find(Actor->GetClass());
		if (ObjectPool)
		{
			ObjectPool->Add(Actor);
		}
	}
	else
	{
		Actor->Destroy();
	}
}
