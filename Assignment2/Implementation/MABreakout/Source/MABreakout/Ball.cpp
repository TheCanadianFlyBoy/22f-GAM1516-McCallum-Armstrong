// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create root
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneComponent;

	//Create collision sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	SphereComponent->SetSphereRadius(75);

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return nullptr;
}

void ABall::Launch()
{
}

