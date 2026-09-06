// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSGameMode.h"
#include "DSCharacter.h"
#include "DSPlayerController.h"
#include "DSMissionSubsystem.h"
#include "Driftshore.h"
#include "Kismet/GameplayStatics.h"

ADSGameMode::ADSGameMode()
{
	DefaultPawnClass = ADSCharacter::StaticClass();
	PlayerControllerClass = ADSPlayerController::StaticClass();
}

void ADSGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogDriftshore, Log, TEXT("Driftshore GameMode ready — Pierline Marina vertical slice."));
}

void ADSGameMode::RestartVerticalSlice()
{
	if (UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (UDSMissionSubsystem* Missions = GI->GetSubsystem<UDSMissionSubsystem>())
			{
				Missions->ResetMissions();
			}
		}
		UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
	}
}
