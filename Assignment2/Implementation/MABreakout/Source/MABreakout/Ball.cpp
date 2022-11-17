// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "PaddlePawn.h"
#include "Board.h"
#include "Powerup.h"
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

	Radius = 10;
	MaxRadius = 30;

	LastHit = nullptr;

	//Create collision sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetSimulatePhysics(false);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
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
	UClass* e = OtherActor->StaticClass();

	//Reflection vector calculation?
	if (!Hit.bStartPenetrating && OtherComp != LastHit) {

		//Handle paddle reflection
		if (OtherActor->ActorHasTag("Paddle"))
		{
			//Get location
			FVector PaddleLocation = OtherActor->GetActorLocation();
			//Cast to Paddle type
			APaddlePawn* Paddle = Cast<APaddlePawn>(OtherActor);
			//Get distance to centre
			float DeltaX = (GetActorLocation().X - PaddleLocation.X);

			//If hitting within the top face
			if (abs(DeltaX) <= Paddle->PaddleLength) {
				//Get angle of reflection based on distance to centre
				float angle = 90 - (DeltaX / Paddle->PaddleLength * 80);
				FRotator NewDirection = FRotator(angle, 0, 0);

				//Displacement
				float distance = Hit.PenetrationDepth; //Get penetration depth
				FVector displacement = NewDirection.Vector() * distance; //Move back along new vector

				//Move ball to impact point, move out of the object, then displace
				SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 10 + displacement, false, nullptr, ETeleportType::ResetPhysics);
				SetActorRotation(NewDirection, ETeleportType::ResetPhysics);
			}
			else
			{
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
				//Handle displacement

				//FVector internalDisplacement = Hit.TraceEnd - Hit.ImpactPoint;
				float distance = Hit.PenetrationDepth;

				FVector displacement = NewVelocity * distance;

				//Displace
				SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 10 + displacement, false, nullptr, ETeleportType::ResetPhysics);
				SetActorRotation(NewDirection, ETeleportType::ResetPhysics);
			}

		}

		//Handle ball deletion
		else if (OtherComp == Board->GetBottom())
		{
			//Decrement ball count, destroy self
			Board->BallCount--;
			this->Destroy();

		}

		//Pass through override
		else if (OtherActor->ActorHasTag("BallPassThrough"))
		{
			//NOTHING - here to avoid any collision with non solid objects
		} 

		//Handle default reflection
		else 
		{
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

	//Get location
	FVector NewLocation = GetActorLocation();
	//Move ball automatically
	if (bMoving) {
		//Move ball with current speed
		NewLocation += GetActorForwardVector() * Speed * DeltaTime;
		//Increment speed over time
		Speed += DeltaTime * 15.0f;
	
	}
	//Set to location
	SetActorLocation(NewLocation, true, nullptr, ETeleportType::ResetPhysics);

}

UPrimitiveComponent* ABall::GetPhysicsComponent()
{
	return SphereComponent;
}

void ABall::Launch()
{
	bMoving = true;
}

//TODO REFACTOR
void ABall::BallBig()
{
	if (Radius < MaxRadius)
	{
		Radius += 1.f;
		Speed -= 5.f;
		Regenerate();
	}
}

void ABall::BallSmall()
{
	if (Radius > MaxRadius/4)
	{
		Radius -= 2.f;
		Speed += 10.f;
		Regenerate();
	}
}

void ABall::BallSplit()
{

}

void ABall::Regenerate()
{
	SphereComponent->SetSphereRadius(Radius);
}

void ABall::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO - remove

}

void ABall::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//TODO - remove
}

