// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DoomHUD.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API ADoomHUD : public AHUD
{
	GENERATED_BODY()
public:
    ADoomHUD();
    UPROPERTY(EditAnywhere, Category = "Game Hud")
        TSubclassOf<class UUserWidget> PlayerGuiClass;

    UPROPERTY()
        class UUserWidget* PlayerGui;

protected:
    virtual void BeginPlay() override;
};
