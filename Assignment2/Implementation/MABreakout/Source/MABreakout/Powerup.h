// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

UCLASS()
class MABREAKOUT_API APowerup : public AActor
{
	GENERATED_BODY()

	enum class EPowerupType {

		PaddlePlus,
		PaddleMinus,
		BallBig,
		BallSmall,
		CompanionPaddle
	};
public:	
	// Sets default values for this actor's properties
	APowerup();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powerup")
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Powerup", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* PowerupFlipbookComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Powerup", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class APaddlePawn> PaddleTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Powerup", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AAIController> ControllerTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaker Ball", meta = (AllowPrivateAccess = "true"))
		class USoundBase* PowerupSound;

		EPowerupType Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Speed for movement
	float Speed;

	//Overlap: only affects paddles
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
