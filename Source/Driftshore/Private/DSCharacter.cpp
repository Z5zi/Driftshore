// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSCharacter.h"
#include "DSVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Driftshore.h"

ADSCharacter::ADSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
}

void ADSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ADSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (JumpAction)
		{
			EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		if (MoveAction)
		{
			EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSCharacter::Move);
		}
		if (LookAction)
		{
			EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSCharacter::Look);
		}
		if (SprintAction)
		{
			EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &ADSCharacter::SprintStarted);
			EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &ADSCharacter::SprintCompleted);
		}
		if (InteractAction)
		{
			EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &ADSCharacter::Interact);
		}
		if (EnterVehicleAction)
		{
			EIC->BindAction(EnterVehicleAction, ETriggerEvent::Started, this, &ADSCharacter::TryEnterVehicle);
		}
		if (MissionPingAction)
		{
			EIC->BindAction(MissionPingAction, ETriggerEvent::Started, this, &ADSCharacter::MissionPing);
		}
	}
}

void ADSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Controller && (Axis.X != 0.f || Axis.Y != 0.f))
	{
		const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Forward, Axis.Y);
		AddMovementInput(Right, Axis.X);
	}
}

void ADSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(Axis.X);
		AddControllerPitchInput(Axis.Y);
	}
}

void ADSCharacter::SprintStarted(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ADSCharacter::SprintCompleted(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ADSCharacter::Interact(const FInputActionValue& Value)
{
	UE_LOG(LogDriftshore, Log, TEXT("Interact pressed — hook pickup / dialogue / mission props here."));
	TryEnterVehicle();
}

void ADSCharacter::MissionPing(const FInputActionValue& Value)
{
	UE_LOG(LogDriftshore, Log, TEXT("Mission ping — highlight active objective."));
}

void ADSCharacter::TryEnterVehicle()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray<FOverlapResult> Overlaps;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(VehicleInteractRange);
	FCollisionQueryParams Params(SCENE_QUERY_STAT(VehicleInteract), false, this);

	const bool bHit = World->OverlapMultiByChannel(
		Overlaps,
		GetActorLocation(),
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		Params);

	if (!bHit)
	{
		return;
	}

	for (const FOverlapResult& Result : Overlaps)
	{
		if (ADSVehiclePawn* Vehicle = Cast<ADSVehiclePawn>(Result.GetActor()))
		{
			Vehicle->TryPossessFrom(this);
			return;
		}
	}
}
