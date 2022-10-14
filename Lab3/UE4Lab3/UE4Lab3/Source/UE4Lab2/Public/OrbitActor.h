// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitActor.generated.h"

UCLASS()
class UE4LAB2_API AOrbitActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbitActor();

	//FORWARD DECLARE a variable called ActorSprite of type UPaperSpriteComponent* as a Property with BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual"
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Actor Visual")
		class UPaperSpriteComponent* ActorSprite;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//DECLARE a variable called AngleAxis of type float
	float AngleAxis;
};
