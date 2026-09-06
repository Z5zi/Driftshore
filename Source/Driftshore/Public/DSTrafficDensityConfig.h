// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "DSTrafficDensityConfig.generated.h"

/**
 * Compile-oriented mirror of Content/Data/traffic_density.json profiles.
 */
USTRUCT(BlueprintType)
struct DRIFTSHORE_API FDSTrafficDensityConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	FName ProfileId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	FName DistrictId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	float VehiclePerKm = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	float PedestrianPer100m2 = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	int32 BoatIdleSlots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	int32 PatrolStubCount = 0;

	/** Multiplier applied for the active lighting / TOD preset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	float TimeOfDayMultiplier = 1.f;
};

/**
 * Pedestrian density slice — kept separate for future DataTable rows.
 */
USTRUCT(BlueprintType)
struct DRIFTSHORE_API FDSPedestrianDensityConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	FName ZoneId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	float PedestrianPer100m2 = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Traffic")
	bool bTouristCluster = false;
};
