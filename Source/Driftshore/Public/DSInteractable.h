// Copyright (c) 2026 Z5zi. Original IP — Driftshore.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DSInteractable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDSInteracted, AActor*, InstigatorActor);

/**
 * Simple interactable volume/actor for crate pickup, doors, booths.
 */
UCLASS(Blueprintable)
class DRIFTSHORE_API ADSInteractable : public AActor
{
	GENERATED_BODY()

public:
	ADSInteractable();

	UFUNCTION(BlueprintCallable, Category = "Driftshore|Interact")
	virtual void Interact(AActor* InstigatorActor);

	UFUNCTION(BlueprintPure, Category = "Driftshore|Interact")
	bool CanInteract() const { return bEnabled && !bConsumed; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Interact")
	FName InteractId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Interact")
	FText PromptText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Interact")
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Driftshore|Interact")
	bool bConsumeOnUse = false;

	UPROPERTY(BlueprintAssignable, Category = "Driftshore|Interact")
	FDSInteracted OnInteracted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Driftshore|Interact")
	TObjectPtr<USceneComponent> RootScene;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Driftshore|Interact")
	bool bConsumed = false;
};
