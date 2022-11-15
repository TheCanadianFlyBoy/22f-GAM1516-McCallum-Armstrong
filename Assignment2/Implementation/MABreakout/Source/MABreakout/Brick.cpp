// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Components/BoxComponent.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	float width = 50;
	float height = 20;

	HealthPoints = 1;
	PowerupChance = 50;

	//Brick Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetBoxExtent(FVector(width, 50, height));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetCollisionProfileName("BlockAllDynamic");
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentHit.AddDynamic(this, &ABrick::OnHit);
	//Lock
	BoxComponent->BodyInstance.bLockRotation = true;
	BoxComponent->BodyInstance.bLockXRotation = true;
	BoxComponent->BodyInstance.bLockYRotation = true;
	BoxComponent->BodyInstance.bLockZRotation = true;
	BoxComponent->BodyInstance.bLockTranslation = true;
	BoxComponent->BodyInstance.bLockXTranslation = true;
	BoxComponent->BodyInstance.bLockYTranslation = true;
	BoxComponent->BodyInstance.bLockZTranslation = true;
	//Root
	SetRootComponent(BoxComponent);

}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABrick::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Ball")) {
		if (HealthPoints <= 1)
		{
			this->Destroy();
			//TODO: powerup
		}
		else {
			HealthPoints--;
		}
	}
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::RollForPowerup()
{
}

