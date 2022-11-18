// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerup.h"
#include "Board.h"
#include "Ball.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaddlePawn.h"
#include "BreakoutAIController.h"
#include "EngineUtils.h" //Needed for TActorIterator

// Sets default values
APowerup::APowerup()
{
	//Add passthrough tag
	Tags.Add("BallPassThrough");
	//Set starter speed
	Speed = 200.0f;

	//Create collison box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("PowerupBox");
	BoxComponent->SetBoxExtent(FVector(20, 0, 20));
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetCollisionProfileName("OverlapAll");
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerup::BeginOverlap);
	SetRootComponent(BoxComponent);

	//Set type TODO: make random
	int TypeRoll = FMath::RandRange(1, 5);
	switch (TypeRoll) {
		case 1: {
			Type = PowerupType::PaddlePlus;
			break;
		}
		case 2: {
			Type = PowerupType::PaddleMinus;
			break;
		}
		case 3: {
			Type = PowerupType::BallSplit;
			break;
		}
		case 4: {
			Type = PowerupType::BallBig;
			break;
		}
		case 5: {
			Type = PowerupType::BallSmall;
			break;
		}
		case 6: {
			Type = PowerupType::CompanionPaddle;
			break;
		}
	}

	//Create sprite
	PowerupFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("PowerupFlipbook");
	PowerupFlipbookComponent->Stop();
	PowerupFlipbookComponent->SetPlaybackPositionInFrames(TypeRoll, true);
	PowerupFlipbookComponent->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
	switch (Type)
	{
		case PowerupType::PaddlePlus:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(2, true);
				break;
			}
			case PowerupType::PaddleMinus:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(3, true);
				break;
			}
			case PowerupType::BallSplit:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(4, true);
				break;
			}
			case PowerupType::BallBig:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(5, true);
				break;
			}
			case PowerupType::BallSmall:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(6, true);
				break;
			}
			case PowerupType::CompanionPaddle:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(7, true);
				break;
			}
	}

}


void APowerup::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			//Call effect
			Paddle->PaddlePlus();
			//TODO PROOF FOR AI PADDLE
			FTimerHandle handle;
			//Callback for end of effect
			GetWorldTimerManager().SetTimer(handle, Paddle, &APaddlePawn::PaddleMinus, 10.0f, false);
			break;
		}
		case PowerupType::PaddleMinus:
		{
			//Call effect
			Paddle->PaddleMinus();
			break;
			FTimerHandle handle;
			//Callback for end of effect
			GetWorldTimerManager().SetTimer(handle, Paddle, &APaddlePawn::PaddlePlus, 10.0f, false);
		}
		case PowerupType::BallSplit:
		{
			//Iterate all balls;
			for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				//Call effect
				ABall* _ball = *ActorItr;
				_ball->BallSplit();
				

			}
			break;
		}
		case PowerupType::BallBig:
		{
			//Iterate all balls;
			for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ABall* _ball = *ActorItr;
				_ball->BallBig();
				//Call timer
				FTimerHandle handle;
				//Callback for end of effect
				GetWorldTimerManager().SetTimer(handle, _ball, &ABall::BallSmall, 10.0f, false);
			}
			break;
		}
		case PowerupType::BallSmall:
		{
			//Iterate all balls;
			for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ABall* _ball = *ActorItr;
				_ball->BallSmall();
				FTimerHandle handle;
				//Callback for end of effect
				GetWorldTimerManager().SetTimer(handle, _ball, &ABall::BallSmall, 10.0f, false);
			}
			break;
		}
		case PowerupType::CompanionPaddle:
		{
			//TODO: AI CONTROLLER!!!

			int count = 0;

			for (TActorIterator<APaddlePawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				count++;
			}

			//Spawn AI paddle
			if (count < 2) {

				//params
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetOwner();
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				//Spawn location
				FVector Location = GetActorLocation();
				FTransform SpawnTransform = FTransform(Location);

				UWorld* _world = GetWorld();

				//Create
				APaddlePawn* _paddle = _world->SpawnActor<APaddlePawn>(APaddlePawn::StaticClass(), SpawnTransform, SpawnParams);
				
				_paddle->AIControllerClass = ABreakoutAIController::StaticClass();
				_paddle->InitialLifeSpan = 10.0f;

			}
			break;
		}
		}

		//Destroy
		this->Destroy();

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

