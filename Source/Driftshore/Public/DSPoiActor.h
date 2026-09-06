// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
class UBillboardComponent;
class USceneComponent;

#include "DSPoiActor.generated.h"

/**
 * Point-of-interest marker for Pierline landmarks / mission nodes.
 * Place in-editor; data mirrors Content/Data/pois.json.
 */
UCLASS(Blueprintable)
class DRIFTSHORE_API ADSPoiActor : public AActor
{
	GENERATED_BODY()

public:
	ADSPoiActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|POI")
	FName PoiId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|POI")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|POI")
	FName DistrictId = TEXT("pierline_marina");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Driftshore|POI")
	FName InteractTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Driftshore|POI")
	TObjectPtr<USceneComponent> RootScene;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, Category = "Driftshore|POI")
	TObjectPtr<UBillboardComponent> EditorSprite;
#endif
};
