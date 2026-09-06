// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DSGameInstance.generated.h"

/**
 * Driftshore game instance — holds slice-wide settings hooks (district focus, TOD preset id).
 */
UCLASS()
class DRIFTSHORE_API UDSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	/** Active district id matching Content/Data/districts.json (e.g. pierline_marina). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|World")
	FName ActiveDistrictId = TEXT("pierline_marina");

	/** Lighting preset id from Content/Data/lighting_presets.json. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|World")
	FName ActiveLightingPresetId = TEXT("pierline_dawn");
};
