// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityWeapon.h"


#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

//WEEK 11 LAB
AGravityWeapon::AGravityWeapon()
{
	/*Setup grab system*/
	//SET IsHoldingObject to false
	IsHoldingObject = false;

	//CREATE the PhysicsHandle 
	PhysicsHandle = CreateDefaultSubobject< UPhysicsHandleComponent>(TEXT("Phymsics"));
	//CREATE the GrabLocation
	GrabLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Gramb"));
	//ATTACH the GrabLocation to the RootComponent
	GrabLocation->SetupAttachment(RootComponent);

	//SET the Relative Location of the GrabLocation to FVector(500.0, 0.0, 0.0)
	GrabLocation->SetRelativeLocation(FVector(500.f, 0.f, 0.f));

	MaxGrabDistance = 1000.0;
	ThrowForce = 500000.0;
	DropDistanceThreshold = 1.5f;
}

//WEEK 11 LAB
void AGravityWeapon::PullTrigger()
{
	//CALL OnGrab()
	OnGrab();
}

//WEEK 11 LAB
void AGravityWeapon::ReleaseTrigger()
{
	//CALL OnThrow()
	OnThrow();
}

//WEEK 11 LAB
void AGravityWeapon::OnGrab()
{
	//IF IsHoldingObject is true
	if (IsHoldingObject) {
		//CALL DropObject()
		DropObject();
	}
	//ELSE
	else {
		//CALL GrabObject()
		GrabObject();
	}
	//ENDIF
}

//WEEK 11 LAB
void AGravityWeapon::OnThrow()
{
	//IF IsHoldingObject is true
	if (IsHoldingObject) {
		//CALL ThrowObject()
		ThrowObject();
	}
	//ENDIF
}

//WEEK 11 LAB
void AGravityWeapon::GrabObject()
{
	//GET the World
	UWorld* World = GetWorld();
	//IF The World IS NOT null
	if (World)
	{
		//DECLARE a FHitResult called hit (Look Up Documentation on FHitResult)
		FHitResult hit = FHitResult();
		//DECLARE a FVector called start and set it to the root components Location
		FVector start = RootComponent->GetComponentLocation();
		//DECLARE a FVector called end and set it to the start + the root components forward vector * MaxGrabDistance
		FVector end = start + RootComponent->GetForwardVector() * MaxGrabDistance;
		//DECLARE a ECollisionChannel called trace and set it to ECC_Visibility
		ECollisionChannel trace = ECC_Visibility;
		//DECLARE a FCollisionQueryParams called queryParams
		FCollisionQueryParams queryParams = FCollisionQueryParams();
		//ADD this actor to the queryParams Ignore list. Make the queryParams Ignore this Actor
		queryParams.AddIgnoredActor(this);

		//DECLARE a FCollisionResponseParams called responseParams
		FCollisionResponseParams responseParams = FCollisionResponseParams();

		//DECLARE a bool called hasHit and do a LineTraceSingleByChannel() passing in hit, start, end, traceChannel, queryParams, responseParams
		bool hasHit = World->LineTraceSingleByChannel(hit, start, end, trace, queryParams, responseParams);
		//IF hasHit is true
		if (hasHit)
		{
			

			//DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 5.f, ECC_WorldStatic, 5.f);
			DrawDebugLine(World, start, end, FColor::Red, false, 5.f, ECC_WorldStatic, 5.f);
			//SET GrabbedObject to the hit objects Actor
			GrabbedObject = hit.GetActor();
			//IF the GrabbedObject is not null
			if (GrabbedObject)
			{
				//SET IsHoldingObject to true
				IsHoldingObject = true;
				//SET GrabbedMesh to the hit Objects Component. Make sure you Cast the hit objects Component as a UMeshComponent
				GrabbedMesh = Cast<UMeshComponent>(hit.GetComponent());
				//CALL GrabComponentAtLocation()  on PhysicsHandle passing in GrabbedMesh, NAME_None, GrabbedMesh->Bounds.GetBox().GetCenter()
				PhysicsHandle->GrabComponentAtLocation(GrabbedMesh, NAME_None, GrabbedMesh->Bounds.GetBox().GetCenter());
			
				//SET the AngularDamping of the GrabbedMesh to 10.0f
				GrabbedMesh->SetAngularDamping(10.f);
				//GrabbedMesh->SetLinearDamping(10);					
				
				/*Play sound*/
				//IF GrabSound is not null
				if (GrabSound)
				{
					//PLAY the GrabSound at this Actors Location
					UGameplayStatics::PlaySoundAtLocation(this, GrabSound, GetActorLocation());
				}
				//ENDIF
			}
			//ENDIF
		}
		//ENDIF
		
	}
	//ENDIF
}

//WEEK 11 LAB
void AGravityWeapon::DropObject()
{

	//CALL ReleaseComponent() on the PhysicsHandle
	PhysicsHandle->ReleaseComponent();
	//CALL SetAngularDamping() on the GrabbedMesh passing in 0.0f
	PhysicsHandle->SetAngularDamping(0.0f);
	//SET IsHoldingObject to false
	IsHoldingObject = false;
}

//WEEK 11 LAB
void AGravityWeapon::ThrowObject()
{
	//CALL DropObject()
	DropObject();

	//DECLARE a FVector called force and assign it to  RootComponent->GetForwardVector() * ThrowForce
	FVector force = RootComponent->GetForwardVector() * ThrowForce;
	//CALL AddImpulse() on GrabbedMesh passing in force
	GrabbedMesh->AddImpulse(force);
	
	/* Play sound */
	//IF ThrowSound NOT nullptr
	if (ThrowSound)
	{
		//PLAY the ThrowSound at this Actors Location
		UGameplayStatics::PlaySoundAtLocation(this, ThrowSound, GetActorLocation());
	}
	//ENDIF
}

//WEEK 11 LAB
void AGravityWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UPDATE Gravity Gun
	UpdateGravityGun(DeltaTime);
}

//WEEK 11 LAB
void AGravityWeapon::UpdateGravityGun(float DeltaTime)
{

	/*Update grabbing location*/
	//CALL SetTargetLocation on the PhysicsHandle passing in the return value of GrabLocation->GetComponentLocation()
	PhysicsHandle->SetTargetLocation(GrabLocation->GetComponentLocation());

	/* Drop if object is too far */
	//IF IsHoldingObject IS true
	if (IsHoldingObject)
	{
		//DECLARE a variable called weaponPosition of type FVector and set it to the return value of RootComponent->GetComponentLocation()
		FVector weaponPosition = RootComponent->GetComponentLocation();
		//DECLARE a variable called meshPosition of type FVector and set it to the return value of GrabbedMesh->GetComponentLocation()
		FVector meshPosition = GrabbedMesh->GetComponentLocation();
		//DECLARE a float value called distance and assign it to the return value of FVector::Distance(weaponPosition, meshPosition)
		float distance = FVector::Distance(weaponPosition, meshPosition);

		//IF distance > MaxGrabDistance * DropDistanceThreshold
		if (distance > MaxGrabDistance * DropDistanceThreshold)
		{
			//CALL DropObject()
			DropObject();
		}
		//ENDIF
	}
	//ENDIF
}