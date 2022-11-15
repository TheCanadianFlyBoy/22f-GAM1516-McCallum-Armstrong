// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BreakoutHUD.generated.h"

/**
 * 
 */
UCLASS()
class MABREAKOUT_API ABreakoutHUD : public AHUD
{
	GENERATED_BODY()

public:
    ABreakoutHUD();
    UPROPERTY(EditAnywhere, Category = "Game Hud")
        TSubclassOf<class UUserWidget> PlayerGuiClass;

    UPROPERTY()
        class UUserWidget* PlayerGui;

protected:
    virtual void BeginPlay() override;
};
