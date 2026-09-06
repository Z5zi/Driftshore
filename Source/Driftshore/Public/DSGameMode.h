// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DSGameMode.generated.h"

/**
 * Default game mode for the Suncove vertical slice.
 */
UCLASS()
class DRIFTSHORE_API ADSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADSGameMode();

	virtual void BeginPlay() override;

	/** Restart the Pier 9 Drop loop after mission summary. */
	UFUNCTION(BlueprintCallable, Category = "Driftshore|Mission")
	void RestartVerticalSlice();
};
