// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DSMissionSubsystem.generated.h"

UENUM(BlueprintType)
enum class EDSMissionState : uint8
{
	Inactive,
	Active,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FDSMissionScore
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float ElapsedSeconds = 0.f;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxPressureTierReached = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bSilentBonus = false;

	UPROPERTY(BlueprintReadOnly)
	int32 CashReward = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDSMissionStateChanged, EDSMissionState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDSMissionScoreReady, FDSMissionScore, Score);

/**
 * Tracks the Pier 9 Drop vertical-slice mission and score hook.
 */
UCLASS()
class DRIFTSHORE_API UDSMissionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Mission")
	void StartMission(FName MissionId);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Mission")
	void CompleteObjective(FName ObjectiveId);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Mission")
	void FailMission(const FString& Reason);

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Mission")
	void ResetMissions();

	UFUNCTION(BlueprintPure, Category = "Driftshore|Mission")
	EDSMissionState GetState() const { return State; }

	UFUNCTION(BlueprintPure, Category = "Driftshore|Mission")
	FName GetActiveMissionId() const { return ActiveMissionId; }

	UFUNCTION(BlueprintPure, Category = "Driftshore|Mission")
	FText GetObjectiveText() const { return ObjectiveText; }

	UPROPERTY(BlueprintAssignable, Category = "Driftshore|Mission")
	FDSMissionStateChanged OnMissionStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Driftshore|Mission")
	FDSMissionScoreReady OnMissionScoreReady;

protected:
	void FinishWithScore(bool bSuccess);

	UPROPERTY()
	EDSMissionState State = EDSMissionState::Inactive;

	UPROPERTY()
	FName ActiveMissionId;

	UPROPERTY()
	FText ObjectiveText;

	double MissionStartTime = 0.0;
	bool bPickedUpCrate = false;
	bool bDeliveredCrate = false;
};
