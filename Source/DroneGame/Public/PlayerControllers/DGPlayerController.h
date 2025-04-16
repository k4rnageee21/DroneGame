#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	FVector GetHitLocationUnderCrosshair(const TArray<AActor*>& IgnoredActors = TArray<AActor*>{}) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Crosshair")
	float CrosshairTraceDistance = 10000.f;
};
