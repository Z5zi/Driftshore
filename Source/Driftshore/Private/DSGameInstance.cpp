// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSGameInstance.h"
#include "Driftshore.h"

void UDSGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogDriftshore, Log, TEXT("DSGameInstance init — district=%s lighting=%s"),
		*ActiveDistrictId.ToString(), *ActiveLightingPresetId.ToString());
}
