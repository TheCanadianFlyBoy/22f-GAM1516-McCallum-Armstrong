// Fill out your copyright notice in the Description page of Project Settings.


#include "OrbitActor.h"
#include "PaperSpriteComponent.h"
// Sets default values
AOrbitActor::AOrbitActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CREATE (Assign) the ActorSprite Component by Calling CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual")
	ActorSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual");

	//SET the RootComponent to the ActorSprite
	RootComponent = ActorSprite;

	//SET AngleAxis to ZERO
	AngleAxis = 0;
}

// Called when the game starts or when spawned
void AOrbitActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// declare arbitrary vector point in the world to circle around
	//DECLARE a variable called NewLocation of type FVector and ASSIGN it to FVector(0, 0, 800)
	FVector NewLocation = FVector(0, 0, 800);

	// declare size of radius to move around
	//DECLARE a variable called Radius of type FVector and Assign it to FVector(200, 0, 0)
	FVector Radius = FVector(200, 0, 0);//For InY and InZ
	//FVector Radius = FVector(0, 200, 0); //For InZ
	//FVector Radius = FVector(0, 0, 200); //For InX

	// angle increases by 1 every frame
	//INCREMENT AngleAxis
	AngleAxis++;

	// prevent number from growind indefinitely
	//IF AngleAxis IS GREATER THAN 360.0f
	if (AngleAxis > 360.0f)
		//SET AngleAxis to 1
	   AngleAxis = 1;
	//ENDIF

	//DECLARE a variable called RotateValue of type FVector and assign it to the return value of  Radius.RotateAngleAxis(AngleAxis, FVector(0, 1, 0))
	FVector RotateValue = Radius.RotateAngleAxis(AngleAxis, FVector(0, 1, 0));

	//ADD RotateValue.X to NewLocation.X i.e NewLocation.X += RotateValue.X
	NewLocation.X += RotateValue.X;
	//ADD RotateValue.Y to NewLocation.Y
	NewLocation.Y += RotateValue.Y;
	//ADD RotateValue.Z to NewLocation.Z
	NewLocation.Z += RotateValue.Z;

	//CALL SetActorLocation() passing in NewLocation
	SetActorLocation(NewLocation);
}

