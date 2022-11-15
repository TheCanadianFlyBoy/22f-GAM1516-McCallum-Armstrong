// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerup.h"
#include "Board.h"
#include "Components/BoxComponent.h"
#include "PaddlePawn.h"

// Sets default values
APowerup::APowerup()
{
	//Set starter speed
	Speed = 200.0f;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("PowerupBox");
	BoxComponent->SetBoxExtent(FVector(20, 0, 20));
	BoxComponent->SetNotifyRigidBodyCollision(true);		//TODO: FIX COLLISION
	SetRootComponent(BoxComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APowerup::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	ABoard* Board = Cast<ABoard>(GetOwner());

	if (OtherActor->ActorHasTag("Paddle"))
	{
		//Cast to paddle
		APaddlePawn* Paddle = Cast<APaddlePawn>(OtherActor);

		//TODO: add powerup logic
		switch (Type)
		{
			case PowerupType::PaddlePlus: 
			{
				
				break;
			}
			case PowerupType::PaddleMinus:
			{

				break;
			}
			case PowerupType::BallSplit:
			{

				break;
			}
			case PowerupType::BallBig:
			{

				break;
			}
			case PowerupType::BallSmall:
			{

				break;
			}
			case PowerupType::CompanionPaddle:
			{
				//TODO: AI CONTROLLER!!!
				break;
			}
		}

	}
	else if (OtherComp == Board->GetBottom()) {
		//Delete self at bottom
		this->Destroy();

	}
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get location
	FVector NewLocation = GetActorLocation();
	NewLocation += FVector(0, 0, -Speed * DeltaTime);

	//Set location
	SetActorLocation(NewLocation, true);

	Speed += DeltaTime;

}

