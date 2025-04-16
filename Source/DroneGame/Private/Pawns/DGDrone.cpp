#include "Pawns/DGDrone.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DGDroneCombatComponent.h"
#include "DataAssets/DGDataAsset_Input.h"
#include "DroneGameTypes/CollisionChannels.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerControllers/DGPlayerController.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

ADGDrone::ADGDrone()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECR_Ignore);

	BodyHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyHitBox"));
	BodyHitBox->SetupAttachment(Mesh);
	BodyHitBox->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECollisionResponse::ECR_Block);

	HeadHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadHitBox"));
	HeadHitBox->SetupAttachment(Mesh);
	HeadHitBox->SetCollisionResponseToChannel(CollisionChannels::Projectile, ECollisionResponse::ECR_Block);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Mesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Mesh);
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
