// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InventoryComponent.h"
#include "InteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API AInteractableDoor : public AInteractable
{
	GENERATED_BODY()
	
public:

	AInteractableDoor();
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class USceneComponent* DoorRoot;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, Category = "DOOM Component")
		class UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, Category = "DOOM Door")
		EKeyColour KeyColour;

	UPROPERTY(EditAnywhere, Category = "DOOM Door")
		bool bLocked;
	UPROPERTY(EditAnywhere, Category = "DOOM Door")
		bool bOpen;

public:
	virtual void OnInteract(APlayerCharacter* InstigatingCharacter) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Open();
	virtual void Close();
};
