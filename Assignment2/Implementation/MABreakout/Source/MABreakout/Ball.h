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
		class UPaperFlipbookComponent* BallFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category  = "Breaker Ball")
		float Speed;

	UPROPERTY(EditAnywhere, Category = "Breaker Ball")
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaker Ball", meta = (AllowPrivateAccess = "true"))
		class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaker Ball", meta = (AllowPrivateAccess = "true"))
		class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breaker Ball", meta = (AllowPrivateAccess = "true"))
		class USoundBase* DeathSound;
	
	//Moving toggle
	bool bMoving;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Radius;
	float MaxRadius;

	UPrimitiveComponent* LastHit;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Launch ball
	void Launch();
	//Sound functions
	void PlayBounce();
	void PlayLaunch();
	void PlayDeath();

	//Powerups
	UFUNCTION()
		void BallBig();
	UFUNCTION()
		void BallSmall();

	//Regenerate
	void Regenerate();

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle sound_debounce_timer;

};
