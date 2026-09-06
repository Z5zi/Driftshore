// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSMissionSubsystem.h"
#include "DSPressureSubsystem.h"
#include "Driftshore.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

void UDSMissionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ResetMissions();
}

void UDSMissionSubsystem::StartMission(FName MissionId)
{
	ActiveMissionId = MissionId.IsNone() ? FName(TEXT("Pier9Drop")) : MissionId;
	State = EDSMissionState::Active;
	bPickedUpCrate = false;
	bDeliveredCrate = false;
	MissionStartTime = FPlatformTime::Seconds();
	ObjectiveText = FText::FromString(TEXT("Collect the sealed crate at slip B."));
	OnMissionStateChanged.Broadcast(State);
	UE_LOG(LogDriftshore, Log, TEXT("Mission started: %s"), *ActiveMissionId.ToString());
}

void UDSMissionSubsystem::CompleteObjective(FName ObjectiveId)
{
	if (State != EDSMissionState::Active)
	{
		return;
	}

	if (ObjectiveId == FName(TEXT("PickupCrate")))
	{
		bPickedUpCrate = true;
		ObjectiveText = FText::FromString(TEXT("Deliver the crate to the warehouse alley."));
		if (UWorld* World = GetWorld())
		{
			if (UGameInstance* GI = World->GetGameInstance())
			{
				if (UDSPressureSubsystem* Pressure = GI->GetSubsystem<UDSPressureSubsystem>())
				{
					Pressure->AddPressure(0.15f, TEXT("CratePickup"));
				}
			}
		}
		UE_LOG(LogDriftshore, Log, TEXT("Objective complete: PickupCrate"));
		return;
	}

	if (ObjectiveId == FName(TEXT("DeliverCrate")) && bPickedUpCrate)
	{
		bDeliveredCrate = true;
		FinishWithScore(true);
	}
}

void UDSMissionSubsystem::FailMission(const FString& Reason)
{
	if (State != EDSMissionState::Active)
	{
		return;
	}
	UE_LOG(LogDriftshore, Warning, TEXT("Mission failed: %s"), *Reason);
	FinishWithScore(false);
}

void UDSMissionSubsystem::ResetMissions()
{
	State = EDSMissionState::Inactive;
	ActiveMissionId = NAME_None;
	ObjectiveText = FText::GetEmpty();
	bPickedUpCrate = false;
	bDeliveredCrate = false;
	MissionStartTime = 0.0;
}

void UDSMissionSubsystem::FinishWithScore(bool bSuccess)
{
	FDSMissionScore Score;
	Score.ElapsedSeconds = static_cast<float>(FPlatformTime::Seconds() - MissionStartTime);

	int32 MaxTier = 0;
	bool bSilent = true;
	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (UDSPressureSubsystem* Pressure = GI->GetSubsystem<UDSPressureSubsystem>())
			{
				MaxTier = Pressure->GetTier();
				bSilent = MaxTier <= 1;
			}
		}
	}

	Score.MaxPressureTierReached = MaxTier;
	Score.bSilentBonus = bSuccess && bSilent;
	Score.CashReward = bSuccess ? (400 + (Score.bSilentBonus ? 150 : 0)) : 0;

	State = bSuccess ? EDSMissionState::Completed : EDSMissionState::Failed;
	ObjectiveText = bSuccess
		? FText::FromString(TEXT("Pier 9 Drop complete."))
		: FText::FromString(TEXT("Mission failed."));

	OnMissionStateChanged.Broadcast(State);
	OnMissionScoreReady.Broadcast(Score);
}
