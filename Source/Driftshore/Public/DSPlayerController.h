// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSPlayerController.generated.h"

/**
 * Player controller for on-foot + vehicle possession handoff.
 */
UCLASS()
class DRIFTSHORE_API ADSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADSPlayerController();

	virtual void BeginPlay() override;

	/** Soft reference to the on-foot pawn when driving (for exit). */
	UPROPERTY(BlueprintReadOnly, Category = "Driftshore|Vehicle")
	TWeakObjectPtr<APawn> CachedOnFootPawn;
};
