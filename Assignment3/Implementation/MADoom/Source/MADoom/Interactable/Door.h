// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UENUM()
	enum class EKeyColour {
		Blue,
		Red,
		Yellow
	};

UCLASS()
class MADOOM_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	bool bLocked;


	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Open();
	void Close();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
