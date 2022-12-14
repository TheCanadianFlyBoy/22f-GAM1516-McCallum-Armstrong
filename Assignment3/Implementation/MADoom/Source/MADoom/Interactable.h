// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class MADOOM_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle CooldownTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Pure virtual interaction
	virtual void OnInteract(class APlayerCharacter* InstigatingCharacter);

};
