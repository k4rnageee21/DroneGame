#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DGObjectPoolSubsystem.generated.h"

USTRUCT()
struct FPoolArray
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<AActor>> ObjectPool;

	bool IsEmpty() const
	{
		return ObjectPool.IsEmpty();
	}

	AActor* Pop()
	{
		return ObjectPool.Pop();
	}

	void Add(AActor* Actor)
	{
		ObjectPool.Add(Actor);
	}
};

UCLASS()
class DRONEGAME_API UDGObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	AActor* GetFromPool(TSubclassOf<AActor> PoolClass, FVector Location, FRotator Rotation);
	void ReturnToPool(AActor* Actor);

private:
	UPROPERTY()
	TMap<TObjectPtr<UClass>, FPoolArray> ObjectPools;
};
