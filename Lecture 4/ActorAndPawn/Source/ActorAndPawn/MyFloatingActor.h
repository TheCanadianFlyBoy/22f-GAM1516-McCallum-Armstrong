// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyFirstActor.h"
#include "MyFloatingActor.generated.h"

/**
 * 
 */
UCLASS()
class ACTORANDPAWN_API AMyFloatingActor : public AMyFirstActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyFloatingActor();

	UPROPERTY(EditAnywhere, Category = Movement)
		float Speed;

	UPROPERTY(EditAnywhere, Category = Movement)
		float XValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float YValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ZValue;

protected:

	float RunningTime;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
