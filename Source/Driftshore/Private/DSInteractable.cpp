// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSInteractable.h"
#include "Driftshore.h"
#include "Components/SceneComponent.h"

ADSInteractable::ADSInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);
}

void ADSInteractable::Interact(AActor* InstigatorActor)
{
	if (!CanInteract())
	{
		return;
	}

	UE_LOG(LogDriftshore, Log, TEXT("Interactable %s used by %s"),
		*InteractId.ToString(),
		InstigatorActor ? *InstigatorActor->GetName() : TEXT("None"));

	OnInteracted.Broadcast(InstigatorActor);

	if (bConsumeOnUse)
	{
		bConsumed = true;
	}
}
