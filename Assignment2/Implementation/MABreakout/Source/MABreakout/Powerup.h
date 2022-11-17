// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

UCLASS()
class MABREAKOUT_API APowerup : public AActor
{
	GENERATED_BODY()

	enum class PowerupType {

		PaddlePlus,
		PaddleMinus,
		BallSplit,
		BallBig,
		BallSmall,
		CompanionPaddle
	};
public:	
	// Sets default values for this actor's properties
	APowerup();

	UPROPERTY()
		class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Speed for movement
	float Speed;
	PowerupType Type;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
