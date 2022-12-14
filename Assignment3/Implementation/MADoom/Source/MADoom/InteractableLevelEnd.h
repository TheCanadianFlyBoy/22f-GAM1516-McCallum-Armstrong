// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableLevelEnd.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API AInteractableLevelEnd : public AInteractable
{
	GENERATED_BODY()

public:
	AInteractableLevelEnd();

	UPROPERTY(EditAnywhere, Category = "DOOM Component")
		class UStaticMeshComponent* MeshComponent;
public:
	virtual void OnInteract(class APlayerCharacter* InstigatorCharacter) override;
	
};
