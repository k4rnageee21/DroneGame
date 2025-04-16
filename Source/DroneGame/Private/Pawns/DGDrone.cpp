#include "Pawns/DGDrone.h"
#include "Camera/CameraComponent.h"
#include "Components/DGDroneCombatComponent.h"
#include "DataAssets/DGDataAsset_Input.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerControllers/DGPlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Interfaces/DGPickupItemInterface.h"

ADGDrone::ADGDrone()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	CombatComponent = CreateDefaultSubobject<UDGDroneCombatComponent>(TEXT("CombatComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ADGDrone::BeginPlay()
{
	Super::BeginPlay();

	SetupDefaultMappingContext();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnMeshOverlap);
}

void ADGDrone::SetupDefaultMappingContext()
{
	APlayerController* PC = GetController<APlayerController>();
	if (!IsValid(PC) || !IsValid(InputDataAsset))
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(InputDataAsset->MappingContext, 0);
	}
}

void ADGDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) && IsValid(InputDataAsset))
	{
		EnhancedInputComponent->BindAction(InputDataAsset->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(InputDataAsset->LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
		EnhancedInputComponent->BindAction(InputDataAsset->ShootAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Shoot);
	}
}

UDGCombatComponent* ADGDrone::GetCombatComponent() const
{
	return CombatComponent.Get();
}

void ADGDrone::Input_Move(const FInputActionValue& Value)
{
	const FVector InputVector = Value.Get<FVector>();
	AddMovementInput(GetActorForwardVector(), InputVector.Y);
	AddMovementInput(GetActorRightVector(), InputVector.X);
	AddMovementInput(GetActorUpVector(), InputVector.Z);
}

void ADGDrone::Input_Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void ADGDrone::Input_Shoot()
{
	if (IsValid(CombatComponent))
	{
		const FVector HitLocation = CombatComponent->GetHitLocationFromController();
		CombatComponent->Shoot(Muzzle->GetComponentLocation(), HitLocation);
	}
}

void ADGDrone::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDGPickupItemInterface* PickUpInterface = Cast<IDGPickupItemInterface>(OtherActor);
	if (PickUpInterface)
	{
		PickUpInterface->PickUp(this);
	}
}
