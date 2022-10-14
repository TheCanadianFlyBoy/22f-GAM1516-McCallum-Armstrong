// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class UE4LAB2_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

	//FORWARD DECLARE a variable called ActorSprite of type UPaperSpriteComponent* as a Property with BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual"
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual")
		class UPaperSpriteComponent* ActorSprite;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//DECLARE a variable called DistancePerTick of type float as a Property with EditAnywhere, Category="Distance Per Tick"
	UPROPERTY(EditAnywhere, Category="Distance Per Tick")
	float DistancePerTick;
};
