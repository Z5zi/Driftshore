// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "DSVehiclePawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UInputMappingContext;
class UInputAction;
class ADSCharacter;

/**
 * Simple driveable pawn stub (marina runabout / coupe).
 * Not a Chaos Vehicle — intentional lightweight prototype.
 */
UCLASS(Blueprintable)
class DRIFTSHORE_API ADSVehiclePawn : public APawn
{
	GENERATED_BODY()

public:
	ADSVehiclePawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Vehicle")
	void TryPossessFrom(ADSCharacter* Driver);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Vehicle")
	void ExitVehicle();

protected:
	void Steer(const FInputActionValue& Value);
	void Throttle(const FInputActionValue& Value);
	void Brake(const FInputActionValue& Value);
	void Handbrake(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> VehicleMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SteerAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> BrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> HandbrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> ExitAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle")
	float MaxSpeed = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle")
	float Acceleration = 1800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle")
	float TurnRate = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle")
	float BrakeStrength = 2400.f;

	float ThrottleInput = 0.f;
	float SteerInput = 0.f;
	float BrakeInput = 0.f;
	bool bHandbrake = false;
	float CurrentSpeed = 0.f;

	UPROPERTY()
	TWeakObjectPtr<ADSCharacter> Occupant;
};
