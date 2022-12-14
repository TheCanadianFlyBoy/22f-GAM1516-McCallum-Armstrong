// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomPlayerState.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Checkpoint.h"

void ADoomPlayerState::OnDamage(float Damage)
{
	if (Armour > 0)
	{
		//Take armour damage
		Armour -= Damage / 2;
		//Calculate bleed damage
		Damage = Damage / (4 * Armour / 100);
	}
	if (Health > 0)
	{
		Health -= Damage;
	}

	//Death check
	if (Health <= 0)
	{
		APlayerCharacter* Player = (APlayerCharacter*)GetPawn();
		Player->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		if (LastCheckpoint && !GetWorldTimerManager().IsTimerActive(LoadTimerHandle))
		{
			GetWorldTimerManager().SetTimer(LoadTimerHandle, this, &ADoomPlayerState::LoadSaveState, 5.f);
		}
	}
}


float ADoomPlayerState::GetAmmo(EAmmoType Type)
{
	//TODO refactor to array?
	switch (Type)
	{
	case EAmmoType::Light:
		return LightAmmo;
		break;
	case EAmmoType::Medium:
		return MediumAmmo;
		break;
	case EAmmoType::Heavy:
		return HeavyAmmo;
		break;
	}

	return -1.f;
}

float ADoomPlayerState::GetHealth() {
	return Health;
}

float ADoomPlayerState::GetArmour() {
	return Armour;
}

float ADoomPlayerState::GetLightAmmo()
{
	return LightAmmo;
}

float ADoomPlayerState::GetMediumAmmo()
{
	return MediumAmmo;
}

float ADoomPlayerState::GetHeavyAmmo()
{
	return HeavyAmmo;
}

void ADoomPlayerState::LoadSaveState()
{
	//Cast
	APlayerCharacter* Player = (APlayerCharacter*)GetPawn();
	LastCheckpoint->LoadSaveState(Player);
}

bool ADoomPlayerState::IsDead()
{
	return (Health <= 0);
}

void ADoomPlayerState::UseAmmo(EAmmoType Type)
{
	switch (Type)
	{
	case EAmmoType::Light: 
		LightAmmo--;
		break;
	case EAmmoType::Medium:
		MediumAmmo--;
		break;
	case EAmmoType::Heavy:
		HeavyAmmo--;
		break;
	}
}

void ADoomPlayerState::AddAmmo(EAmmoType Type, float Amount)
{
	switch (Type)
	{
	case EAmmoType::Light:
		LightAmmo+=Amount;
		break;
	case EAmmoType::Medium:
		MediumAmmo+=Amount;
		break;
	case EAmmoType::Heavy:
		HeavyAmmo+=Amount;
		break;
	}
}

void ADoomPlayerState::BeginPlay()
{
	//Call super
	Super::BeginPlay();

	//Set opening health to max, armour to none
	Health = 100.f;
	Armour = 0.f;
}
