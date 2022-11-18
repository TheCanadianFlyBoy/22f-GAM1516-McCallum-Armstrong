// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleLength = 80.f;
	PaddleMax = 150.f;

	Speed = 300.0f;

	Tags.Add("Paddle"); //Add lookup tag

	//Collision Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	BoxComponent->SetBoxExtent(FVector(PaddleLength, 50, 10));
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetCollisionProfileName("BlockAllDynamic");
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->BodyInstance.bNotifyRigidBodyCollision = true;
	//Collision Locks
	BoxComponent->GetBodyInstance()->bLockRotation = true;
	BoxComponent->GetBodyInstance()->bLockXRotation = true;
	BoxComponent->GetBodyInstance()->bLockYRotation = true;
	BoxComponent->GetBodyInstance()->bLockZRotation = true;
	//BoxComponent->GetBodyInstance()->bLockTranslation = true;
	BoxComponent->GetBodyInstance()->bLockYTranslation = true;
	BoxComponent->GetBodyInstance()->bLockZTranslation = true;
	//BoxComponent->GetBodyInstance()->bLockXTranslation = true;
	//BoxComponent->GetBodyInstance()->bLockXTranslation = true;
	SetRootComponent(BoxComponent);

	//Sprite
	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("PaddleSprite");
	PawnSpriteComponent->SetSimulatePhysics(false);
	PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PawnSpriteComponent->SetupAttachment(RootComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	//IF MovementForward NOT EQUAL to 0
	if (MovementRight != 0)
	{
		//ASSIGN NewLocation to the the sum of the Actors Current Location and the product of the Actors Forward Vector and the MovementForward value i.e GetActorLocation() + (GetActorForwardVector() * MovementForward)
		NewLocation = GetActorLocation() + (GetActorForwardVector() * MovementRight * Speed * DeltaTime);
	}
	else {
		BoxComponent->SetPhysicsLinearVelocity(FVector::ZeroVector, false);
	}


	//CALL SetActorLocation() passing in NewLocation
	SetActorLocation(NewLocation, true, (FHitResult*) nullptr, ETeleportType::ResetPhysics);


}

// Called to bind functionality to input
void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APaddlePawn::MoveRight(float value)
{
	MovementRight = value;
}

void APaddlePawn::PaddlePlus()
{
	//Check if can lengthen
	if (PaddleLength < PaddleMax)
	{
		//Increment
		PaddleLength += 10.f;
		//Regen paddle
		Regenerate();
	}
}

void APaddlePawn::PaddleMinus()
{
	//Check if can lengthen
	if (PaddleLength > PaddleMax/4)
	{
		//Increment
		PaddleLength -= 10.f;
		//Regen padle
		Regenerate();
	}
}

//Regenerates the box component/sprite
void APaddlePawn::Regenerate()
{
	BoxComponent->SetBoxExtent(FVector(PaddleLength, 50, 10));
	float scale = PaddleLength / (80.f / 2.f);
	PawnSpriteComponent->SetRelativeScale3D(FVector(scale, 2.f, 2.f));
	//Reset position by jiggling
	MoveRight(1.0f);
	MoveRight(-1.0f);
}

void APaddlePawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%s has Hit"), *OtherActor->GetName()));
		}
	}
}

