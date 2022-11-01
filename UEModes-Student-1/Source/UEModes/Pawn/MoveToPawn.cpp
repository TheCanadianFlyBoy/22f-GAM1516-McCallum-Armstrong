// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPawn.h"
#include "PaperSpriteComponent.h"
// Sets default values
AMoveToPawn::AMoveToPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");

	PawnSpriteComponent->SetSimulatePhysics(true);

	//RootComponent = PawnSpriteComponent;
	//          OR
	SetRootComponent(PawnSpriteComponent);
}

// Called when the game starts or when spawned
void AMoveToPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveToPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//IF Target is NOT EQUAL to nullptr
	if (Target != nullptr)
	{
		//DECLARE a variable called targetLocation of type FVector and assign it to the return value of FMath::VInterpConstantTo(..) passing in --> GetActorLocation(), Target->GetActorLocation(), DeltaTime, 600.0f
		FVector targetLocation = FMath::VInterpConstantTo(GetActorLocation(), Target->GetActorLocation(), DeltaTime, 600.0f);
		//CALL  SetActorLocation(..) passing in targetLocation
		SetActorLocation(targetLocation);
	}
	//ENDIF Target is NOT EQUAL to nullptr
}

// Called to bind functionality to input
void AMoveToPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

