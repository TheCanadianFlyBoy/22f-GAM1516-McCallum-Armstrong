// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActor.h"
#include <Components/SphereComponent.h>
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "PaperSpriteComponent.h"

#include "MyBlueprintFunctionLibrary.h"
// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sprite->SetCollisionProfileName("NoCollision");


    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereCollision->SetSphereRadius(24.f);
    RootComponent = SphereCollision;
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereCollision->SetCollisionProfileName("OverlapAll");
    SphereCollision->SetGenerateOverlapEvents(true);


    SphereCollision->SetSimulatePhysics(false);

    Sprite->SetupAttachment(RootComponent);
    SphereCollision->SetConstraintMode(EDOFMode::SixDOF);
    //SphereCollision->SetupAttachment(RootComponent);
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(SphereCollision);
    Tags.Add("Pickup");
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Get the root primitive component.
	//Primitive = Cast<UPaperSpriteComponent>(GetRootComponent());
	//if (Primitive)
	//{
	//	if (PickupMode == EPickupMode::AutoPickup)
	//	{
	//		Primitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);			
	//		Primitive->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//		Primitive->SetCollisionResponseToAllChannels(ECR_Ignore);
	//		Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); //??? Or whateever other Object
	//	}
	//}
	//check(Primitive != nullptr && "Actor is mising a primitive component!");
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}


void APickupActor::Disable()
{
	if (Sprite)
	{
		this->SetActorHiddenInGame(true);
        SphereCollision->SetActive(false);

        SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APickupActor::Enable()
{
	if (Sprite)
	{
		this->SetActorHiddenInGame(false);
        SphereCollision->SetActive(true);

        SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

