#include "PlayerControllers/DGPlayerController.h"
#include "Components/DGDroneCombatComponent.h"
#include "Components/DGHealthComponent.h"
#include "Pawns/DGDrone.h"
#include "HUDs/DGHUD.h"
#include "UI/DGStatsWidget.h"

void ADGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimerForNextTick(this, &ThisClass::Init);
}

void ADGPlayerController::Init()
{
	CacheValues();
	InitHUD();
}

void ADGPlayerController::CacheValues()
{
	DroneHUD = GetHUD<ADGHUD>();
	Drone = GetPawn<ADGDrone>();
	if (!IsValid(Drone))
	{
		return;
	}
	DroneCombatComponent = Drone->GetDroneCombatComponent();
	DroneHealthComponent = Drone->GetHealthComponent();
}

void ADGPlayerController::InitHUD()
{
	UpdateHUD();
	BindHUDCallbacks();
}

void ADGPlayerController::UpdateHUD()
{
	if (!IsValidHUD())
	{
		return;
	}

	if (IsValid(DroneCombatComponent))
	{
		DroneHUD->StatsWidget->SetAmmo(DroneCombatComponent->GetAmmo());
	}
	if (IsValid(DroneHealthComponent))
	{
		DroneHUD->StatsWidget->SetHealth(DroneHealthComponent->GetHealth());
	}
}

void ADGPlayerController::BindHUDCallbacks()
{
	if (!IsValid(DroneCombatComponent) || !IsValid(DroneHealthComponent))
	{
		return;
	}

	DroneCombatComponent->OnAmmoChanged.AddDynamic(this, &ThisClass::HandleAmmoChanged);
	DroneHealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::HandleHealthChanged);
}

bool ADGPlayerController::IsValidHUD() const
{
	return IsValid(DroneHUD) && IsValid(DroneHUD->StatsWidget);
}

void ADGPlayerController::HandleAmmoChanged(int32 NewAmmo)
{
	if (IsValidHUD())
	{
		DroneHUD->StatsWidget->SetAmmo(NewAmmo);
	}
}

void ADGPlayerController::HandleHealthChanged(float NewHealth)
{
	if (IsValidHUD())
	{
		DroneHUD->StatsWidget->SetHealth(NewHealth);
	}
}

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
