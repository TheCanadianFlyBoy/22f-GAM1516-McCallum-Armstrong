// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ADoomHUD::ADoomHUD()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/WBP_DoomUI"));
    //if (playerHud.Succeeded())
    if (playerHud.Succeeded()) {
        PlayerGuiClass = playerHud.Class;
    }
}

void ADoomHUD::BeginPlay()
{
    Super::BeginPlay();
    //CREATE the PlayerGui widget by assigning the return value of CreateWidget<UUserWidget>() passing in: GetGameInstance(), PlayerGuiClass
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(), PlayerGuiClass);
    //CALL AddToViewport() on PlayerGui
    PlayerGui->AddToViewport();
}
