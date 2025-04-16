#pragma once

#include "CoreMinimal.h"
#include "Pawns/DGPawnBase.h"
#include "DGDrone.generated.h"

class UBoxComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UDGDroneCombatComponent;
class UDGDataAsset_Input;
struct FInputActionValue;

UCLASS(Abstract)
class DRONEGAME_API ADGDrone : public ADGPawnBase
{
	GENERATED_BODY()

public:
	ADGDrone();

	/*	Start Pawn interface	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/*	End Pawn interface		*/

	FORCEINLINE UDGDroneCombatComponent* GetDroneCombatComponent() const { return CombatComponent; }

protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	/*	Start Input callbacks	*/
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Shoot();
	/*	End Input callbacks		*/

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UBoxComponent> BodyHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UBoxComponent> HeadHitBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UDGDroneCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	TObjectPtr<UDGDataAsset_Input> InputDataAsset;
};
