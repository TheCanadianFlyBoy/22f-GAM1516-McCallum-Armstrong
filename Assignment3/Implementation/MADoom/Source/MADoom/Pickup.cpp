// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Weapon.h"
#include "PaperFlipbookComponent.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create sphere root
	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Sphere"));
	PickupSphere->SetSphereRadius(100.f);
	PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupSphere->SetCollisionProfileName("OverlapAll");
	PickupSphere->SetGenerateOverlapEvents(true);
	//Setup dynamics
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);

	SetRootComponent(PickupSphere);

	//Create sprite
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		//CAST
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		//Cases
		switch (PickupType)
		{
		case EPickupType::Weapon:
		{
			//Check if player has weapon
			if (!Player->InventoryComponent->HasWeapon(WeaponTemplate.GetDefaultObject()->WeaponName)) {
				//Create new weapon!
				//Create parameters
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Player;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FVector SpawnLocation = GetActorLocation();
				FTransform SpawnTransform = FTransform(SpawnLocation);

				//Spawn
				AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponTemplate, SpawnTransform, SpawnParams);
				Player->InventoryComponent->AddWeapon(NewWeapon);
				//Unequip weapon and equip new weapon
				
				
			}
			break;
		}
		case EPickupType::Ammo:
		{
			break;
		}
		case EPickupType::Health:
		{
			break;
		}



		}

		//Delete self
		this->Destroy();

	}
}