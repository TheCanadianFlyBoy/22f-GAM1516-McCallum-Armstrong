// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "MovingActor.generated.h"

UCLASS()
class UE4LAB2_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual")
		UPaperSpriteComponent* ActorSprite;

	UPROPERTY(EditAnywhere, Category = "Distance Per Tick")
		float DistancePerTick;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
