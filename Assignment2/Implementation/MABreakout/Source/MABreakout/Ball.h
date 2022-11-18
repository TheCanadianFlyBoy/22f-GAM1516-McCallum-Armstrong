// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class MABREAKOUT_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Sphere")
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker Ball")
		class UPaperSpriteComponent* BallSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breaker Ball")
		class UPaperFlipbookComponent* BallFlipbook;
	
	UPROPERTY(VisibleAnywhere, Category = "Breaker Ball")
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category  = "Breaker Ball")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Breaker Ball")
		float MaxSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bMoving;
	float Radius;
	float MaxRadius;

	UPrimitiveComponent* LastHit;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Get sphere
	UPrimitiveComponent* GetPhysicsComponent();

	//Launch ball
	void Launch();

	//Powerups
	UFUNCTION()
		void BallBig();
	UFUNCTION()
		void BallSmall();
	UFUNCTION()
		void BallSplit();

	UFUNCTION() //TODO ???
		void Resize(float value);

	//Regenerate
	void Regenerate();

private:

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
