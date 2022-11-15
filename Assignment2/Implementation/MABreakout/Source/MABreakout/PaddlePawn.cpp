// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleLength = 100.f;
	PaddleMax = 200.f;

	Speed = 300.0f;

	Tags.Add("Paddle"); //Add lookup tag

	//Collision Box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	BoxComponent->SetBoxExtent(FVector(PaddleLength, 50, 10));
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetEnableGravity(false);
	BoxComponent->SetCollisionProfileName("BlockAllDynamic");
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Collision Locks
	BoxComponent->GetBodyInstance()->bLockRotation = true;
	BoxComponent->GetBodyInstance()->bLockXRotation = true;
	BoxComponent->GetBodyInstance()->bLockYRotation = true;
	BoxComponent->GetBodyInstance()->bLockZRotation = true;
	BoxComponent->GetBodyInstance()->bLockYTranslation = true;
	BoxComponent->GetBodyInstance()->bLockZTranslation = true;
	//BoxComponent->GetBodyInstance()->bLockXTranslation = true;
	SetRootComponent(BoxComponent);

	//Sprite
	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("PaddleSprite");
	PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//PawnSpriteComponent->SetupAttachment(RootComponent);

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

