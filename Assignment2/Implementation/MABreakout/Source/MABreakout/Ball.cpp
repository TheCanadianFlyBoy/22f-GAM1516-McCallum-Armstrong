// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "PaddlePawn.h"
#include "Board.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

FVector ClampVectorTo2D(FVector& _vector) {
	_vector.Y = 0;
	return _vector;
}

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 200.0f;
	MaxSpeed = 3000000.0f;
	bMoving = true;

	LastHit = nullptr;

	//Create collision sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(10);
	SphereComponent->SetSimulatePhysics(false);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABall::BeginOverlap);
	//Lock
	SphereComponent->BodyInstance.bLockRotation = true;
	SphereComponent->BodyInstance.bLockXRotation = true;
	SphereComponent->BodyInstance.bLockYRotation = true;
	SphereComponent->BodyInstance.bLockZRotation = true;
	SphereComponent->BodyInstance.bLockTranslation = true;
	SphereComponent->BodyInstance.bLockYTranslation = true;
	SphereComponent->BodyInstance.bLockXTranslation = true;
	SphereComponent->BodyInstance.bLockZTranslation = true;

	SetRootComponent(SphereComponent);

	Tags.Add("Ball");

}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	//TODO: error catching
	ABoard* Board = Cast<ABoard>(GetOwner());

	//Reflection vector calculation?
	if (!Hit.bStartPenetrating && OtherComp != LastHit) {
		if (OtherActor->ActorHasTag("Paddle"))
		{
			//TODO: paddle math
			FVector PaddleLocation = OtherActor->GetActorLocation();
			APaddlePawn* Paddle = Cast<APaddlePawn>(OtherActor);

			float DeltaX = (GetActorLocation().X - PaddleLocation.X);

			//Get angle
			float angle = 90 - (DeltaX/Paddle->PaddleLength * 80);
			FRotator NewDirection = FRotator(angle, 0, 0);

			//Displacement
			//FVector internalDisplacement = Hit.TraceEnd - Hit.ImpactPoint;
			float distance = Hit.PenetrationDepth;
			FVector displacement = NewDirection.Vector() * distance;

			//Move ball
			SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 10 + displacement, false, nullptr, ETeleportType::ResetPhysics);
			SetActorRotation(NewDirection, ETeleportType::ResetPhysics);
		}
		else if (OtherComp == Board->GetBottom())
		{
			Board->BallCount--;
			this->Destroy();
		} else {
			//Direction change
			//Get current direction
			FRotator Direction = GetActorRotation();
			//Get vector format and clamp to 2D plane
			FVector IncidentVector = Direction.Vector();
			IncidentVector = ClampVectorTo2D(IncidentVector);
			//Get normal vector and clamp to 2D plane
			FVector NormalVector = Hit.ImpactNormal;
			NormalVector = ClampVectorTo2D(NormalVector);

			//Find dot prduct DEBUGGING TODO REMOVE
			float IncidentDotImpulse = IncidentVector | NormalVector;
			FVector x = 2.0f * ((IncidentVector | NormalVector) * NormalVector);

			//Find reflection vector
			FVector NewVelocity = IncidentVector - 2.0f * ((IncidentVector | NormalVector) * NormalVector);
			//Set new direction
			//FRotator NewDirection = NewVelocity.Rotation();
			float angle = atan2(NewVelocity.Z, NewVelocity.X);
			angle = FMath::RadiansToDegrees(angle);
			FRotator NewDirection = FRotator(angle, 0, 0);
			//FQuat NewDirection = FQuat(NewVelocity.Rotation());

		

			//TODO REFACTOR
			float boardWidth = 500;
			float boardHeight = 500;
			float borderWidth = 10;
			//Handle displacement

			//FVector internalDisplacement = Hit.TraceEnd - Hit.ImpactPoint;
			float distance = Hit.PenetrationDepth;

			FVector displacement = NewVelocity * distance;

			//Displace
			SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 10 + displacement, false, nullptr, ETeleportType::ResetPhysics);
			SetActorRotation(NewDirection, ETeleportType::ResetPhysics);

		}
	
		//Debounce double hits
		LastHit = OtherComp;

	}

}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	//Move ball automatically
	if (bMoving) {

		NewLocation += GetActorForwardVector() * Speed * DeltaTime;

		Speed += DeltaTime * 15.0f;
	
	}

	SetActorLocation(NewLocation, true, nullptr, ETeleportType::ResetPhysics);

}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return SphereComponent;
}

void ABall::Launch()
{
}

void ABall::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

}

void ABall::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

