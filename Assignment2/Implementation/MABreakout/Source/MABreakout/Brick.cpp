// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Powerup.h"
#include "Components/BoxComponent.h"
#include "PaperFlipBookComponent.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	float width = 50;
	float height = 20;

	HealthPoints = 1;
	PowerupChance = 100;

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

	BrickFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("BrickFlipbook");
	BrickFlipbook->Stop();
	BrickFlipbook->SetPlaybackPositionInFrames(HealthPoints - 1, true);
	BrickFlipbook->SetupAttachment(RootComponent);

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
			RollForPowerup();
			this->Destroy();
			//TODO: powerup
		}
		else {
			//Subtract health
			HealthPoints--;
			//Update flipbook
			UpdateSprite();
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
	//Roll for random
	float Roll = FMath::RandRange(0.f, 100.f);

	if (Roll <= PowerupChance) {
		//params
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//Spawn location
		FVector Location = GetActorLocation();
		FTransform SpawnTransform = FTransform(Location);

		UWorld* _world = GetWorld();

		//Create
		APowerup* _powerup = _world->SpawnActor<APowerup>(PowerupTemplate, SpawnTransform, SpawnParams);
	}
}

void ABrick::UpdateSprite()
{
	int frame = HealthPoints+1;
	BrickFlipbook->SetPlaybackPositionInFrames(frame, true);
}

