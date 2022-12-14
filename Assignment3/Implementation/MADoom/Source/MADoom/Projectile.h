// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MADOOM_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	//Components
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class USphereComponent* ProjectileSphere;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class UExplosiveComponent* ExplosiveComponent;
	//Sprites
	UPROPERTY(EditAnywhere, Category = "DOOM Component")
		class UPaperFlipbookComponent* SpriteComponent;
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* ProjectileSprite;
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* ImpactSprite;
	//Stats
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Speed;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float AreaOfEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//On hit
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
