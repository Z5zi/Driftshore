// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSTimeOfDaySubsystem.h"
#include "Driftshore.h"

void UDSTimeOfDaySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ActivePresetId = TEXT("pierline_dawn");
	TimeOfDayHours = 6.5f;
	UE_LOG(LogDriftshore, Log, TEXT("TimeOfDay subsystem ready (stub)."));
}

void UDSTimeOfDaySubsystem::Tick(float DeltaTime)
{
	if (!bAutoAdvance || DayLengthSeconds <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	const float HoursPerSecond = 24.f / DayLengthSeconds;
	TimeOfDayHours = FMath::Fmod(TimeOfDayHours + DeltaTime * HoursPerSecond + 24.f, 24.f);
}

TStatId UDSTimeOfDaySubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UDSTimeOfDaySubsystem, STATGROUP_Tickables);
}

void UDSTimeOfDaySubsystem::SetPreset(FName PresetId)
{
	ActivePresetId = PresetId;
	UE_LOG(LogDriftshore, Log, TEXT("TOD preset -> %s (apply lights in-editor / BP)"), *PresetId.ToString());
}

void UDSTimeOfDaySubsystem::SetTimeOfDayHours(float Hours)
{
	TimeOfDayHours = FMath::Fmod(FMath::Max(0.f, Hours), 24.f);
}
