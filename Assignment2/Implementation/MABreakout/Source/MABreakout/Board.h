// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class MABREAKOUT_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	//Enum for sides
	enum class BoardSide {
		Bottom = 0,
		Left = 1,
		Top = 2,
		Right = 3
	};

	// Sets default values for this actor's properties
	ABoard();

public: // members
	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "SceneRoot")
		class UBoxComponent* BoardRoot;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Bricks")
		TArray<class ABrick*> Bricks;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Bounding")
		TArray<class UBoxComponent*> BoxColliders;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Camera")
		class UCameraComponent* BoardCamera;

	UPROPERTY(VisibleAnywhere, Category = "Paddle")
		class APaddlePawn* PlayerPaddle;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SpawnPowerup(ABrick* _brick);
	UFUNCTION()
		void SpawnBall(APaddlePawn* _paddle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Box component hit
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
