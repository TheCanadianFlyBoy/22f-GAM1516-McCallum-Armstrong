// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCollision.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "UEModes/Actors/Ball.h"
// Sets default values
ATriggerCollision::ATriggerCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");

	TriggerBox->SetBoxExtent(FVector(120, 50, 140)); //100,10,100

	TriggerBox->SetSimulatePhysics(false);

	TriggerBox->SetCollisionProfileName("OverlapAllDynamic");
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerCollision::BeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATriggerCollision::EndOverlap);

	SetRootComponent(TriggerBox);
	
}

void ATriggerCollision::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapping Actor = %s"), *OtherActor->GetName()));
		}
	}
}

void ATriggerCollision::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Ended"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%s has left the Trigger Volume"), *OtherActor->GetName()));
		}


		if (OtherActor->IsA<ABall>())
		{
			OtherActor->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ATriggerCollision::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), 
	       GetActorLocation(), 
				 TriggerBox->GetUnscaledBoxExtent(), 
				 FColor::Green,
   true, 
         999, 
		0, 
		5);
}

// Called every frame
void ATriggerCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

