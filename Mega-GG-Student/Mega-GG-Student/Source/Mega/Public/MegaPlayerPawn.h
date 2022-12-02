// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MegaPlayerPawn.generated.h"

enum class EInventoryDirection : unsigned char;
UENUM(BlueprintType)		//"BlueprintType" is important to include
enum class EDirectionEnum : uint8
{
	DE_Right 	UMETA(DisplayName = "Right"),
	DE_Left 	UMETA(DisplayName = "Left")
};

UCLASS()
class MEGA_API AMegaPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMegaPlayerPawn();

	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess))
		class UCapsuleComponent* CapsuleComponent; //class USphereComponent* SphereComponent;

        /** Pickup Ball Trigger  */
    UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess))
        class USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/** camera boom  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;
	//class USphereComponent* SphereComponent;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UInventoryComponent* InventoryComponent;

    UFUNCTION()
        void NextWeapon();

    UFUNCTION()
        void PrevWeapon();

    UFUNCTION()
        void PickupWeapon();

    UFUNCTION()
        void FireWeapon();

	UFUNCTION()
		void PullWeaponTrigger();
	UFUNCTION()
		void ReleaseWeaponTrigger();

 
        class AWeaponActor* CurrentWeapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float value);
	void MoveUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EDirectionEnum DirectionEnum;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* PlayerSprite;
private:
	float MovementRight;
	bool bJump;

	void EquipFromInventory(EInventoryDirection dir);
};
