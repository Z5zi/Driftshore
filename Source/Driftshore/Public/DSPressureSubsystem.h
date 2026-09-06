// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DSPressureSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDSPressureChanged, float, NormalizedPressure, int32, Tier);

/**
 * Pressure (heat) — original naming for street attention / escalation.
 * Tiers drive ambient chatter density and checkpoint stub spawns (wired later).
 */
UCLASS()
class DRIFTSHORE_API UDSPressureSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Pressure")
	void AddPressure(float Amount, FName Reason);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Pressure")
	void SetDecayEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Pressure")
	void ResetPressure();

	UFUNCTION(BlueprintPure, Category = "Driftshore|Pressure")
	float GetNormalizedPressure() const { return Pressure; }

	UFUNCTION(BlueprintPure, Category = "Driftshore|Pressure")
	int32 GetTier() const;

	UPROPERTY(BlueprintAssignable, Category = "Driftshore|Pressure")
	FDSPressureChanged OnPressureChanged;

	/** Per-second decay while in quiet zones (wetlands / interiors). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Pressure")
	float DecayPerSecond = 0.05f;

protected:
	UFUNCTION()
	void TickDecay();

	void BroadcastIfChanged(int32 PreviousTier);

	UPROPERTY()
	float Pressure = 0.f;

	bool bDecayEnabled = true;
	FTimerHandle DecayTimerHandle;
	int32 LastBroadcastTier = 0;
	float DecayIntervalSeconds = 0.25f;
};
