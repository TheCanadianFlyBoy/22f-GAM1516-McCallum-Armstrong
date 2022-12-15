// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
//Components
#include "SaveStateComponent.h"
#include "Components/SphereComponent.h"
//References
#include "PlayerCharacter.h"
#include "DoomPlayerState.h"
#include "InventoryComponent.h"
#include "EnemyCharacter.h"
//Utils
#include "EngineUtils.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create save component
	SaveComponent = CreateDefaultSubobject<USaveStateComponent>(TEXT("Save Component"));
	
	//Create sphere component
	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetSphereRadius(100.f);	//Default radius
	TriggerZone->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);	//Set collision enabled
	TriggerZone->SetCollisionProfileName("OverlapAll");
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);	//Subscribe
	SetRootComponent(TriggerZone);	//Root

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}
//Save State
void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If player
	if (OtherActor->ActorHasTag("Player"))
	{
		//Cast to Player
		APlayerCharacter* Player = dynamic_cast<APlayerCharacter*>(OtherActor);
		ADoomPlayerState* State = dynamic_cast<ADoomPlayerState*>(Player->GetPlayerState());
		//Save state
		SaveComponent->SetSaveStateParams(Player);
		State->LastCheckpoint = this;
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::LoadSaveState(APlayerCharacter* Player)
{
	//Cast state
	ADoomPlayerState* State = (ADoomPlayerState*) Player->GetPlayerState();
	//Get params
	FDOOMSaveStateParams& SavedParams = SaveComponent->GetSaveStateParams();
	//Override state - TODO make into a function
	State->Health = SavedParams.Health;
	State->Armour = SavedParams.Armour;
	State->LightAmmo = SavedParams.LightAmmo;
	State->MediumAmmo = SavedParams.MediumAmmo;
	State->HeavyAmmo = SavedParams.HeavyAmmo;
	//Teleport player
	Player->SetActorLocation(SavedParams.Location);

	//Move enemies

	for (TActorIterator<AEnemyCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->ReloadCharacter();
	}

}

