// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSPlayerController.h"
#include "Driftshore.h"

ADSPlayerController::ADSPlayerController()
{
	bShowMouseCursor = false;
}

void ADSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogDriftshore, Verbose, TEXT("DSPlayerController BeginPlay"));
}
