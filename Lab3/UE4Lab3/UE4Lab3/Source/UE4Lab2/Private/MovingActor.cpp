// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"
#include "PaperSpriteComponent.h"
// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CREATE (Assign) the ActorSprite Component by Calling CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual")
	ActorSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual");
	//SET the RootComponent to the ActorSprite
	RootComponent = ActorSprite;
	
	//Actor will be able to move only one meter in any direction
	//SET DistancePerTick to a default value i.e 100
	DistancePerTick = 100;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	//How far we can move multiplied by what direction we move in gives us direction and length of our movement
	//DECLARE a variable called MovementVector of type FVector and ASSIGN it to the product of the Actors Forward Vector and DistancePerTick i.e  GetActorForwardVector() * DistancePerTick
	FVector MovementVector = GetActorForwardVector() * DistancePerTick;
	//To get our new location, we take the current location and add the distance+direction we are going to travel
	//DECLARE a variable called NewLocation of type FVector and ASSIGN it to the sum of the Actors Current Location and the MovementVector Multiplied by DeltaTime i.e  GetActorLocation() + MovementVector * DeltaTime
	FVector NewLocation = GetActorLocation() + MovementVector * DeltaTime;

	//CALL SetActorLocation() passing in NewLocation
	SetActorLocation(NewLocation);
}

