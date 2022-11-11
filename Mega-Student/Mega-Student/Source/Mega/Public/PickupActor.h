// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"


UCLASS()
class MEGA_API APickupActor : public AActor
{
	GENERATED_BODY()
#pragma region Region_Private

#pragma endregion Region_Private

#pragma region Region_Public
public:	
	// Sets default values for this actor's properties
	APickupActor();
		
	UFUNCTION()//, WithValidation)
	virtual void Disable();

	UFUNCTION()//, WithValidation)
	virtual void Enable();

#pragma endregion Region_Public

#pragma region Region_Protected
protected:
    /* sphere collision  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Components")
        class USphereComponent* SphereCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	    class UPaperSpriteComponent* Sprite;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
#pragma endregion Region_Protected
};
