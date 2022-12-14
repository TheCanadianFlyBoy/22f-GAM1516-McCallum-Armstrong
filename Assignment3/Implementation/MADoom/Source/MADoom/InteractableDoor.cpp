// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
//Components
#include "Components/StaticMeshComponent.h" //TODO geometry
#include "Components/BoxComponent.h"
//References
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

AInteractableDoor::AInteractableDoor() : Super()
{
	//Create root component
	DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Door Root Location"));
	SetRootComponent(DoorRoot);

	//Create mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);;
	MeshComponent->SetCollisionProfileName("BlockAllDynamic");
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	BoxCollider->SetBoxExtent(FVector(100, 25, 150));
	BoxCollider->SetCollisionProfileName("BlockAllDynamic");
	BoxCollider->SetupAttachment(MeshComponent);

}

void AInteractableDoor::OnInteract(APlayerCharacter* InstigatingCharacter)
{
	if (GetWorldTimerManager().IsTimerActive(CooldownTimerHandle)) return;
	else GetWorldTimerManager().SetTimer(CooldownTimerHandle, 5.f, false);

	if (bLocked)
	{
		if (InstigatingCharacter->InventoryComponent->HasKey(KeyColour))
		{
			bLocked = false;
		}
	}

	//Recheck lock
	if (!bLocked) {
		if (bOpen) Close();
		else		Open();
	}
}

void AInteractableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector DeltaLocation = MeshComponent->GetComponentLocation() - GetActorLocation();
	if (bOpen)
	{
		if (DeltaLocation.Z < 300)
		{
			MeshComponent->AddLocalOffset(FVector(0, 0, 100 * DeltaTime));
		}
	} else {
		if (DeltaLocation.Z > 0)
		{
			MeshComponent->AddLocalOffset(FVector(0, 0, -100 * DeltaTime));
		}
		else MeshComponent->SetRelativeLocation(FVector(0, 0, 0));
	}
}


void AInteractableDoor::Open()
{
	bOpen = true;
}

void AInteractableDoor::Close()
{
	bOpen = false;
}