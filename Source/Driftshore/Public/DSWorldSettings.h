// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "DSTrafficDensityConfig.h"
#include "DSWorldSettings.generated.h"

/**
 * World settings for Suncove maps — district focus + default traffic density profile.
 */
UCLASS()
class DRIFTSHORE_API ADSWorldSettings : public AWorldSettings
{
	GENERATED_BODY()

public:
	ADSWorldSettings();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|World")
	FName DefaultDistrictId = TEXT("pierline_marina");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|World")
	FDSTrafficDensityConfig DefaultTrafficDensity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|World")
	FName DefaultLightingPresetId = TEXT("pierline_dawn");
};
