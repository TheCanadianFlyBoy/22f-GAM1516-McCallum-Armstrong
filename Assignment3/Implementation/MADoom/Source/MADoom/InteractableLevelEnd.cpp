// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableLevelEnd.h"
//Components
#include "Components/StaticMeshComponent.h"
//References
#include "DoomGameState.h"

AInteractableLevelEnd::AInteractableLevelEnd() : Super()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);;
	MeshComponent->SetCollisionProfileName("BlockAll");
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);

}

void AInteractableLevelEnd::OnInteract(class APlayerCharacter* InstigatorCharacter)
{
	ADoomGameState* GameState = dynamic_cast<ADoomGameState*>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->CompleteLevel();
	}
}