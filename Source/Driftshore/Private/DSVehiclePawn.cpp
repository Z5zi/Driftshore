// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSVehiclePawn.h"
#include "DSCharacter.h"
#include "DSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Driftshore.h"

ADSVehiclePawn::ADSVehiclePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->InitBoxExtent(FVector(120.f, 60.f, 40.f));
	CollisionBox->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = CollisionBox;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void ADSVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADSVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsPlayerControlled())
	{
		return;
	}

	const float TargetAccel = (ThrottleInput * Acceleration) - (BrakeInput * BrakeStrength);
	CurrentSpeed = FMath::Clamp(CurrentSpeed + TargetAccel * DeltaTime, bHandbrake ? 0.f : -MaxSpeed * 0.35f, MaxSpeed);

	if (bHandbrake)
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.f, DeltaTime, 4.f);
	}

	if (!FMath::IsNearlyZero(CurrentSpeed))
	{
		const float YawDelta = SteerInput * TurnRate * DeltaTime * FMath::Clamp(CurrentSpeed / MaxSpeed, -1.f, 1.f);
		AddActorWorldRotation(FRotator(0.f, YawDelta, 0.f));
		AddActorWorldOffset(GetActorForwardVector() * CurrentSpeed * DeltaTime, true);
	}
}

void ADSVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (SteerAction)
		{
			EIC->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ADSVehiclePawn::Steer);
			EIC->BindAction(SteerAction, ETriggerEvent::Completed, this, &ADSVehiclePawn::Steer);
		}
		if (ThrottleAction)
		{
			EIC->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ADSVehiclePawn::Throttle);
			EIC->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ADSVehiclePawn::Throttle);
		}
		if (BrakeAction)
		{
			EIC->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ADSVehiclePawn::Brake);
			EIC->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ADSVehiclePawn::Brake);
		}
		if (HandbrakeAction)
		{
			EIC->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &ADSVehiclePawn::Handbrake);
			EIC->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &ADSVehiclePawn::Handbrake);
		}
		if (ExitAction)
		{
			EIC->BindAction(ExitAction, ETriggerEvent::Started, this, &ADSVehiclePawn::ExitVehicle);
		}
	}
}

void ADSVehiclePawn::TryPossessFrom(ADSCharacter* Driver)
{
	if (!Driver)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(Driver->GetController());
	if (!PC)
	{
		return;
	}

	Occupant = Driver;
	if (ADSPlayerController* DSPC = Cast<ADSPlayerController>(PC))
	{
		DSPC->CachedOnFootPawn = Driver;
	}

	Driver->SetActorHiddenInGame(true);
	Driver->SetActorEnableCollision(false);
	Driver->DisableInput(PC);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		if (VehicleMappingContext)
		{
			Subsystem->AddMappingContext(VehicleMappingContext, 1);
		}
	}

	PC->Possess(this);
	UE_LOG(LogDriftshore, Log, TEXT("Entered vehicle %s"), *GetName());
}

void ADSVehiclePawn::ExitVehicle()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC || !Occupant.IsValid())
	{
		return;
	}

	ADSCharacter* Driver = Occupant.Get();
	const FVector ExitLoc = GetActorLocation() + GetActorRightVector() * 150.f + FVector(0.f, 0.f, 50.f);
	Driver->SetActorLocation(ExitLoc);
	Driver->SetActorHiddenInGame(false);
	Driver->SetActorEnableCollision(true);
	Driver->EnableInput(PC);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		if (VehicleMappingContext)
		{
			Subsystem->RemoveMappingContext(VehicleMappingContext);
		}
	}

	ThrottleInput = SteerInput = BrakeInput = 0.f;
	CurrentSpeed = 0.f;
	PC->Possess(Driver);
	Occupant.Reset();
	UE_LOG(LogDriftshore, Log, TEXT("Exited vehicle"));
}

void ADSVehiclePawn::Steer(const FInputActionValue& Value)
{
	SteerInput = Value.Get<float>();
}

void ADSVehiclePawn::Throttle(const FInputActionValue& Value)
{
	ThrottleInput = Value.Get<float>();
}

void ADSVehiclePawn::Brake(const FInputActionValue& Value)
{
	BrakeInput = Value.Get<float>();
}

void ADSVehiclePawn::Handbrake(const FInputActionValue& Value)
{
	bHandbrake = Value.Get<float>() > 0.5f;
}
