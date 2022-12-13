// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EAmmoType : uint8 {
	Light	,
	Medium	,
	Heavy	
};

UCLASS()
class MADOOM_API AWeapon : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AWeapon();
	//Sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DOOM Visuals")
		class UPaperFlipbookComponent* SpriteComponent;
	//WeaponStats
	UPROPERTY(EditAnywhere, Category = "DOOM Weapon Stats")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "DOOM Weapon Stats")
		float RateOfFire;
	UPROPERTY(EditAnywhere, Category = "DOOM Weapon Stats")
		 EAmmoType AmmoType;
	UPROPERTY(EditAnywhere, Category = "DOOM Weapon Stats")
		class AProjectile* ProjectileTemplate;
	UPROPERTY(EditAnywhere, Category = "DOOM Weapon Stats")
		FName WeaponName;
	//Sound
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DOOM Sound")
		class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Sound")
		class USoundBase* FireSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DOOM Sound");
		UPawnNoiseEmitterComponent* NoiseEmitter;

	//Allows for overriding of fire (future enemy implementation?)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	bool bCanFire;
	FTimerHandle WeaponTimerHandle;
	float WeaponRange;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Fire Control
	void BeginFireTimer();
	void EndFireTimer();

	//Equip/unequip
	void Equip(class APlayerCharacter* Player);
	void Unequip();

private: 

	//Traces
	bool GetPickableActor_LineTraceTestByChannel(ECollisionChannel CollisionChannel);
	AActor* GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel);
	AActor* GetPickableActor_SphereTraceSingleByChannel(ECollisionChannel CollisionChannel);
	TArray<FHitResult> GetPickableActor_LineTraceMultiByChannel(ECollisionChannel CollisionChannel);
	//Setup ray trace
	void SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace);
	void SetupTraceParams(FCollisionQueryParams& TraceParams);

};
