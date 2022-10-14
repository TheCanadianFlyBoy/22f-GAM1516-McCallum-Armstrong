// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "FlyingPawn.h"

// Sets default values
AFlyingPawn::AFlyingPawn():
	bGrowing(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerRoot = CreateDefaultSubobject<USceneComponent>("Player Root");
	SetRootComponent(PlayerRoot);

	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PawnSpriteComponent->SetupAttachment(RootComponent);//Attach to RootComponent

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);//Attach to RootComponent
	//Set SpringArm Properties
	SpringArm->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Pawns Camera");
	FollowCamera->SetupAttachment(SpringArm);//Attach to SpringArm
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(6000.0f);
	FollowCamera->bUsePawnControlRotation = false;

	//Auto possess the Pawnand Receive Player0's Input.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create the SimplePawnMovementComponent
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("CustomMovementComponent"));
	//Set the SimplePawnMovementComponent's UpdateComponent to the RootComponent. This will apply the movement to the RootComponent
	FloatingPawnMovement->UpdatedComponent = RootComponent;
	FloatingPawnMovement->Acceleration = 3500.0f;
	FloatingPawnMovement->Deceleration = 8000.0f;
	FloatingPawnMovement->TurningBoost = 8.0f;
	FloatingPawnMovement->MaxSpeed = 1000.0f;

}

// Called when the game starts or when spawned
void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyingPawn::StartGrowing()
{
	bGrowing = true;
}

void AFlyingPawn::StopGrowing()
{
	bGrowing = false;
}

void AFlyingPawn::FlyUp(float value)
{
		FloatingPawnMovement->AddInputVector(GetActorUpVector() * value * 1000);
}

void AFlyingPawn::FlyRight(float value)
{

	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * value * 1000);

	if (value > 0) {
		MovingRight();
	}
	else if (value < 0) {
		MovingLeft();
	}
}

void AFlyingPawn::MovingLeft()
{
	SetDirection(FVector::BackwardVector);
}

void AFlyingPawn::MovingRight()
{
	SetDirection(FVector::ForwardVector);
}

void AFlyingPawn::SetDirection(const FVector Direction)
{
	if (Direction == FVector::ForwardVector) {
		PawnSpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));
	} 
	else if (Direction == FVector::BackwardVector)
	{
		PawnSpriteComponent->SetRelativeRotation(FRotator(0, 180, 0));
	}
}

// Called every frame
void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentScale = PawnSpriteComponent->GetComponentScale().X;

	if (bGrowing)
	{
		CurrentScale += DeltaTime;
	}
	else {
		CurrentScale -= DeltaTime / 2;
	}

	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);

	PawnSpriteComponent->SetWorldScale3D(FVector(CurrentScale));

}

// Called to bind functionality to input
void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind the Input Command FlyRight, to this Object. When FlyRight is Pressed we call the Function MoveForward()
	PlayerInputComponent->BindAxis("FlyRight", this, &AFlyingPawn::FlyRight);
	//Bind the Input Command FlyUp, to this Object. When FlyRight is Pressed we call the Function MoveUp()
	PlayerInputComponent->BindAxis("FlyUp", this, &AFlyingPawn::FlyUp);

	// Bind Input to trigger Grow on pressed.
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AFlyingPawn::StartGrowing);
	//Bind input to stop growing on release
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AFlyingPawn::StopGrowing);

}

