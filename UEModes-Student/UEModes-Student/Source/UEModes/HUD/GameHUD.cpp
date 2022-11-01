// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AGameHUD::AGameHUD()
{
    
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/WBP_PlayerUI"));
    //if (playerHud.Succeeded())
    if (playerHud.Succeeded()) {
        PlayerGuiClass = playerHud.Class;
    }
    //    PlayerGuiClass = playerHud.Class;
    
}
void AGameHUD::BeginPlay()
{
    Super::BeginPlay();
    //CREATE the PlayerGui widget by assigning the return value of CreateWidget<UUserWidget>() passing in: GetGameInstance(), PlayerGuiClass
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(), PlayerGuiClass);
    //CALL AddToViewport() on PlayerGui
    PlayerGui->AddToViewport();
    

}
