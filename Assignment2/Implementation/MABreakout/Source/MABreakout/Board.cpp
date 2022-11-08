// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoard::ABoard()
{

	float boardWidth = 500, boardHeight = 500;
	float borderWidth = 10;
	//ROOT
	BoardRoot = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	BoardRoot->SetBoxExtent(FVector(boardWidth, 10, boardHeight));
	RootComponent = BoardRoot;


	//BOX COLLISION
	//Bottom Trigger Zone
	UBoxComponent* bottom = CreateDefaultSubobject<UBoxComponent>("BoardBottom");
	bottom->SetupAttachment(BoardRoot);
	bottom->SetBoxExtent(FVector(boardWidth, 10, borderWidth));
	bottom->SetSimulatePhysics(false);
	bottom->SetCollisionProfileName("OverlapAllDynamic");
	bottom->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bottom->AddLocalOffset(FVector(0, 0, -(boardHeight + borderWidth)));
	//Add dynamics
	bottom->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
	bottom->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);
	//Sides - LEFT //TODO REFACTOR TO FUNCTION?
	UBoxComponent* left = CreateDefaultSubobject<UBoxComponent>("BoardLeft");
	left->SetBoxExtent(FVector(borderWidth, 10, boardHeight));
	left->SetupAttachment(BoardRoot);
	left->AddLocalOffset(FVector(-(boardWidth + borderWidth), 0, 0));
	//Sides - RIGHT
	UBoxComponent* right = CreateDefaultSubobject<UBoxComponent>("BoardRight");
	right->SetBoxExtent(FVector(borderWidth, 10, boardHeight));
	right->SetupAttachment(BoardRoot);
	right->AddLocalOffset(FVector((boardWidth + borderWidth), 0, 0));
	//SIDES TOP
	UBoxComponent* top = CreateDefaultSubobject<UBoxComponent>("BoardTop");
	top->SetBoxExtent(FVector(boardWidth, 10, borderWidth));
	top->SetupAttachment(BoardRoot);
	top->AddLocalOffset(FVector(0, 0, boardHeight + borderWidth));

	//CAMERA
	BoardCamera = CreateDefaultSubobject<UCameraComponent>("BoardCamera");
	BoardCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	BoardCamera->SetOrthoWidth(5000.0f);
	BoardCamera->SetAspectRatio(boardWidth / boardHeight); //TODO: figure out aspect ratio
	BoardCamera->SetupAttachment(BoardRoot);
	BoardCamera->AddLocalRotation(FRotator(0, -90, 0));
	BoardCamera->AddLocalOffset(FVector(-500, 0, 0));
	BoardCamera->bUsePawnControlRotation = false;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABoard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABoard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABoard::SpawnPowerup(ABrick* _brick)
{
}

void ABoard::SpawnBall(APaddlePawn* _paddle)
{
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoard::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

