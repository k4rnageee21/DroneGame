#pragma once

#include "CoreMinimal.h"
#include "Pawns/DGPawnBase.h"
#include "Interfaces/DGCombatInterface.h"
#include "DGDrone.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;
class UDGDroneCombatComponent;
class UDGDataAsset_Input;
struct FInputActionValue;

UCLASS(Abstract)
class DRONEGAME_API ADGDrone : public ADGPawnBase, public IDGCombatInterface
{
	GENERATED_BODY()

public:
	ADGDrone();

	/*	Start Pawn interface	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/*	End Pawn interface		*/

	FORCEINLINE UDGDroneCombatComponent* GetDroneCombatComponent() const { return CombatComponent; }
	virtual UDGCombatComponent* GetCombatComponent() const override;

protected:
	/*	Start Actor interface	*/
	virtual void BeginPlay() override;
	/*	End Actor interface		*/

	/*	Start Input callbacks	*/
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Shoot();
	/*	End Input callbacks		*/

	void SetupDefaultMappingContext();

	UFUNCTION()
	void OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UDGDroneCombatComponent> CombatComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	TObjectPtr<UDGDataAsset_Input> InputDataAsset;
};
