// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StarFoxPawn.h"
#include "StarFox.h"


AStarFoxPawn::AStarFoxPawn()
{
	// Structure to hold one-time initialization. This can be done in another file or some other place 
	struct FConstructorStatics
	{
        //StaticMesh'/Game/Flying/Meshes/UFO.UFO'
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
            : PlaneMesh(TEXT("StaticMesh'/Game/Flying/Meshes/UFO.UFO'"))
			//: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
    //TODO 4: Initialize/Create the ShipMesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Mesh");
    //TODO 5: Set the StaticMesh on the ShipMesh component to the UFO using "ConstructorStatics.PlaneMesh.Get()"
	ShipMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
    //TODO 6: SET the RootComponent to the SHipMesh Component
	SetRootComponent(ShipMesh);

	// Create a spring arm component
    //TODO 7: Initialize/Create the SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
    //TODO 8: Attach it to the RootComponent
	SpringArm->SetupAttachment(RootComponent);
    //TODO 9: SET the SpringArm's TargetArmLength to a appropriate value, this will set the camera to follow at a distance behind the character
	SpringArm->TargetArmLength = 250.f;
    //TODO 10: SET the SpringArm's SocketOffset, assign it to a FVector(0.f,0.f, ?.0f)
	SpringArm->SocketOffset = FVector(0.f, 0.f, 15.f);
    //TODO 11: Set the bEnableCameraLag on the SprinArm to false, disabling the camera lag, set it to true to see what happens as well
	SpringArm->bEnableCameraLag = false;
    //TODO 12: SET the CameraLagSpeed on the SpringArm to ? 
	SpringArm->CameraLagSpeed = 0.f;
	

	// Create camera component 
    //TODO 13: Initialize/Create the Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera de mon Ship");
    //TODO 14: Attach the Camera to the SprinArm
	Camera->SetupAttachment(SpringArm);
    //TODO 15: SET the bUsePawnControlRotation to false on the Camera, this will tell the camera not to rotate camera with the controller
	Camera->bUsePawnControlRotation = false;

	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 400000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}

void AStarFoxPawn::Tick(float DeltaSeconds)
{
    //TODO 16: Declare a const FVector variable called LocalMove and assign it to FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f), remember X is our Forward
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);
     
    // Move Ship forward (with sweep so we stop when we collide with things)
    //TODO 17: CALL AddActorLocalOffset() passing in LocalMove and true, the second parameter of true tells it to sweep, so we stop when we collide with things
    //Look up the function in the documentation	
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
    //TODO 18: Declare a FRotator called DeltaRotation Initialized to (0,0,0)
	FRotator DeltaRotation = FRotator::ZeroRotator;
    //TODO 19: SET the DeltaRotation Pitch to CurrentPitchSpeed * DeltaSeconds
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
    //TODO 20: SET the DeltaRotation Yaw to CurrentYawSpeed * DeltaSeconds
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
    //TODO 21: SET the DeltaRotation Roll to CurrentRollSpeed * DeltaSeconds
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate Ship
    //TODO 22: CALL AddActorLocalRotation passing in DeltaRotation
	AddActorLocalRotation(DeltaRotation);

	// Call any parent class Tick implementation
    //TODO 23: Call Super:Tick(...)
	Super::Tick(DeltaSeconds);
	

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}

void AStarFoxPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    //TODO 24: Call Super::NotifyHit(...)
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
    //TODO 25:  Declare a FRotator called CurrentRotation and set to to the return value of GetActorRotation() 
	FRotator CurrentRotation = GetActorRotation();
	
    //TODO 26: CALL SetActorRotation() and pass in a Slerp'd Rotation using FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f)
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}

//TODO 27: REVIEW the contents of this Function. Look up the "check" function
void AStarFoxPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Thrust", this, &AStarFoxPawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AStarFoxPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AStarFoxPawn::MoveRightInput);
}

void AStarFoxPawn::ThrustInput(float Val)
{
	
	// Is there no input?
    //TODO 28: Declare a bool called bHasInput and check whether there is input, if Val is 0, there is no input. SET the bHasInput to true or false
	bool bHasInput = Val == 0 ? false : true;

	if (bHasInput) UE_LOG(LogTemp, Log, TEXT("WHAT"));
	// If input is not held down, reduce speed
    //TODO 29: Declare a float called CurrentAcc, if there is input(bHasInput == true) then SET CurrentAcc to (Val * Acceleration), otherwise SET CurrentAcc to (-0.5f * Acceleration) slowing it down
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
	
	// Calculate new speed
    //TODO 30: Declare a float called NewForwardSpeed and SET it to CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc)
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	
	// Clamp between MinSpeed and MaxSpeed
    //TODO 31: SET the CurrentForwardSpeed by clamping NewForwardSpeed between MinSpeed and MaxSpeed use FMath::Clamp(...)
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}

void AStarFoxPawn::MoveUpInput(float Val)
{
	// Target pitch speed is based in input
    //TODO 32: Declare a float variable called TargetPitchSpeed and SET it to (Val * TurnSpeed * -1.f)
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
    //TODO 33: SET TargetPitchSpeed by Incrementing it (+=) with the Absolute value of the CurrentYawSpeed Multiplied by -0.2 --> (FMath::Abs(CurrentYawSpeed) * -0.2f)
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2);

	// Smoothly interpolate to target pitch speed
    //TODO 34: SET the CurrentPitchSpeed to a new Interpolated value using FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f)
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}

void AStarFoxPawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
    //TODO 35: Declare a float called TargetYawSpeed and SET it to Val * TurnSpeed
	float TargetYawSpeed = Val * TurnSpeed;

	// Smoothly interpolate to target yaw speed
    //TODO 36: SET the CurrentYawSpeed to a new Interpolated value using FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f)
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
    //TODO 37: Declare a const bool called bIsTurning and SET it to FMath::Abs(Val) > 0.2f
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value
    //TODO 38: Declare a float Called TargetRollSpeed and using the Ternary operator SET it to bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f). GET USED TO USING THE Ternary Operator
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
    //TODO 39: SET the CurrentRollSpeed to a new Interpolated value using FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f)
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

    //TODO COMPILE: COMPILE AND MAKE SURE IT RUNS (COMPILE OFTEN)
}