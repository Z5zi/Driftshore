// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#include "DSPoiActor.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"

ADSPoiActor::ADSPoiActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

#if WITH_EDITORONLY_DATA
	EditorSprite = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorSprite"));
	EditorSprite->SetupAttachment(RootScene);
	EditorSprite->bIsScreenSizeScaled = true;
#endif
}
