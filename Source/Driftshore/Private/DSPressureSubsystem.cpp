// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSPressureSubsystem.h"
#include "Driftshore.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UDSPressureSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ResetPressure();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			DecayTimerHandle,
			this,
			&UDSPressureSubsystem::TickDecay,
			DecayIntervalSeconds,
			true);
	}
}

void UDSPressureSubsystem::Deinitialize()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(DecayTimerHandle);
	}
	Super::Deinitialize();
}

void UDSPressureSubsystem::AddPressure(float Amount, FName Reason)
{
	const int32 PrevTier = GetTier();
	Pressure = FMath::Clamp(Pressure + Amount, 0.f, 1.f);
	UE_LOG(LogDriftshore, Log, TEXT("Pressure +%.2f (%s) -> %.2f tier %d"),
		Amount, *Reason.ToString(), Pressure, GetTier());
	BroadcastIfChanged(PrevTier);
}

void UDSPressureSubsystem::SetDecayEnabled(bool bEnabled)
{
	bDecayEnabled = bEnabled;
}

void UDSPressureSubsystem::ResetPressure()
{
	Pressure = 0.f;
	LastBroadcastTier = 0;
	OnPressureChanged.Broadcast(Pressure, GetTier());
}

int32 UDSPressureSubsystem::GetTier() const
{
	if (Pressure < 0.25f) return 0;
	if (Pressure < 0.50f) return 1;
	if (Pressure < 0.75f) return 2;
	return 3;
}

void UDSPressureSubsystem::TickDecay()
{
	if (!bDecayEnabled || Pressure <= 0.f)
	{
		return;
	}
	const int32 PrevTier = GetTier();
	Pressure = FMath::Max(0.f, Pressure - DecayPerSecond * DecayIntervalSeconds);
	BroadcastIfChanged(PrevTier);
}

void UDSPressureSubsystem::BroadcastIfChanged(int32 PreviousTier)
{
	const int32 NewTier = GetTier();
	if (NewTier != PreviousTier || NewTier != LastBroadcastTier)
	{
		LastBroadcastTier = NewTier;
	}
	OnPressureChanged.Broadcast(Pressure, NewTier);
}
