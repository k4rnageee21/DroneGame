#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

class ADGDrone;
class UDGDroneCombatComponent;
class UDGHealthComponent;
class ADGHUD;

UCLASS(Abstract)
class DRONEGAME_API ADGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	FVector GetHitLocationUnderCrosshair(const TArray<AActor*>& IgnoredActors = TArray<AActor*>{}) const;

protected:
	virtual void BeginPlay() override;

	void Init();
	void CacheValues();
	void InitHUD();
	void UpdateHUD();
	void BindHUDCallbacks();
	bool IsValidHUD() const;

	/*	Start UI callbacks 		*/
	UFUNCTION()
	void HandleAmmoChanged(int32 NewAmmo);

	UFUNCTION()
	void HandleHealthChanged(float NewHealth);
	/*	End UI callbacks 		*/

	UPROPERTY(BlueprintReadOnly, Category = "Cached Data")
	TObjectPtr<ADGDrone> Drone;

	UPROPERTY(BlueprintReadOnly, Category = "Cached Data")
	TObjectPtr<UDGDroneCombatComponent> DroneCombatComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Cached Data")
	TObjectPtr<UDGHealthComponent> DroneHealthComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Cached Data")
	TObjectPtr<ADGHUD> DroneHUD;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Crosshair")
	float CrosshairTraceDistance = 10000.f;
};
