// Fill out your copyright notice in the Description page of Project Settings.

//"If you spill it, run."

#include "Ball.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("SceneRoot");
	CollisionSphere->SetSphereRadius(75); //cm
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionProfileName("BlockAllDynamic");
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionSphere->GetBodyInstance()->bLockYTranslation = 0;
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	//Subscribe to hit, callback
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	
	SetRootComponent(CollisionSphere);

	BallSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Paper Sprite Component"));
	BallSprite->SetupAttachment(RootComponent);
	BallSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);//Disable the Collision so that the
																		  //Sprite does not collide with the
																		  //Collision Sphere
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return  Cast<UPrimitiveComponent>(CollisionSphere);
}


void ABall::Destroyed()
{
	Super::Destroyed();
	GEngine->AddOnScreenDebugMessage(-1,
		5.f,
		FColor::Black,
		FString::Printf(TEXT("BALL DESTROYED")));
}


void ABall::OnHit(	UPrimitiveComponent* HitComponent, 
					AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, 
					FVector NormalImpulse,
					const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, //Layer
				0.5f, //Linger time
				FColor::Magenta, //Colour
				FString::Printf(TEXT("%s has Hit"), *OtherActor->GetName()) //Text
			);
		}
	}
}


