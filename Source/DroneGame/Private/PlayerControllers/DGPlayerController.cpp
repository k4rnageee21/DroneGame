#include "PlayerControllers/DGPlayerController.h"

FVector ADGPlayerController::GetHitLocationUnderCrosshair(const TArray<AActor*>& IgnoredActors) const
{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint(CameraLocation, CameraRotation);

	const FVector CameraDirection = CameraRotation.Vector();
	const FVector TraceStart = CameraLocation;
	const FVector TraceEnd = TraceStart + CameraDirection * CrosshairTraceDistance;

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetPawn());
	QueryParams.AddIgnoredActors(IgnoredActors);
	UWorld* World = GetWorld();
	check(IsValid(World));

	bool bHit = World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	return bHit ? Hit.Location : TraceEnd;
}
