// Fill out your copyright notice in the Description page of Project Settings.


#include "Powerup.h"
#include "Board.h"
#include "Ball.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaddlePawn.h"
#include "BreakoutAIController.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/GameplayStatics.h"

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

	//Set type TODO: Implement missing powerups
	int TypeRoll = FMath::RandRange(1,5);
	switch (TypeRoll) {
		case 1: {
			Type = EPowerupType::PaddlePlus;
			break;
		}
		case 2: {
			Type = EPowerupType::PaddleMinus;
			break;
		};
		case 3: {
			Type = EPowerupType::BallBig;
			break;
		}
		case 4: {
			Type = EPowerupType::BallSmall;
			break;
		}
		case 5: {
			Type = EPowerupType::CompanionPaddle;
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
		case EPowerupType::PaddlePlus:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(1, true);
				break;
			}
			case EPowerupType::PaddleMinus:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(2, true);
				break;
			}
			case EPowerupType::BallBig:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(3, true);
				break;
			}
			case EPowerupType::BallSmall:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(4, true);
				break;
			}
			case EPowerupType::CompanionPaddle:
			{
				PowerupFlipbookComponent->SetPlaybackPositionInFrames(5, true);
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
		UGameplayStatics::PlaySoundAtLocation(this, PowerupSound, GetActorLocation());

		//TODO: add powerup logic
		switch (Type)
		{
		case EPowerupType::PaddlePlus:
		{
			//Call effect
			Paddle->PaddlePlus();
			//TODO proof for AI paddle
			break;
		}
		case EPowerupType::PaddleMinus:
		{
			//Call effect
			Paddle->PaddleMinus();
			break;
		}
		case EPowerupType::BallBig:
		{
			//Iterate all balls;
			for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ABall* _ball = *ActorItr;
				_ball->BallBig();
			}
			break;
		}
		case EPowerupType::BallSmall:
		{
			//Iterate all balls;
			for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				ABall* _ball = *ActorItr;
				_ball->BallSmall();
			}
			break;
		}
		case EPowerupType::CompanionPaddle:
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
				FVector Location = FVector(GetActorLocation().X, 0, -460);
				FTransform SpawnTransform = FTransform(Location);

				UWorld* _world = GetWorld();

				//Create
				APaddlePawn* _paddle = _world->SpawnActor<APaddlePawn>(PaddleTemplate, SpawnTransform, SpawnParams);
				
				_paddle->AIControllerClass = ControllerTemplate;
				_paddle->SpawnDefaultController();
				_paddle->Controller->SetPawn(_paddle);
				_paddle->SetLifeSpan(20.0f);	//TODO: implement lifespan extension!

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

