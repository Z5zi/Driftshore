// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DSTimeOfDaySubsystem.generated.h"

/**
 * Stub time-of-day controller. Apply presets from Content/Data/lighting_presets.json in Blueprint/C++ later.
 * Does not drive actual lights until authored in-editor.
 */
UCLASS()
class DRIFTSHORE_API UDSTimeOfDaySubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable, Category = "Driftshore|TOD")
	void SetPreset(FName PresetId);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|TOD")
	void SetTimeOfDayHours(float Hours);

	UFUNCTION(BlueprintPure, Category = "Driftshore|TOD")
	FName GetActivePresetId() const { return ActivePresetId; }

	UFUNCTION(BlueprintPure, Category = "Driftshore|TOD")
	float GetTimeOfDayHours() const { return TimeOfDayHours; }

	/** When true, advances TimeOfDayHours using DayLengthSeconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|TOD")
	bool bAutoAdvance = false;

	/** Real-time seconds for a full 24h cycle when auto-advancing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|TOD", meta = (ClampMin = "60.0"))
	float DayLengthSeconds = 1200.f;

protected:
	UPROPERTY()
	FName ActivePresetId = TEXT("pierline_dawn");

	UPROPERTY()
	float TimeOfDayHours = 6.5f;
};
