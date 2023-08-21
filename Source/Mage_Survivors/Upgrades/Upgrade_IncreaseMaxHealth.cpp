// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade_IncreaseMaxHealth.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/HealthComponent.h"

UUpgrade_IncreaseMaxHealth::UUpgrade_IncreaseMaxHealth()
{}

void UUpgrade_IncreaseMaxHealth::DoAction()
{
	_player->GetHealthComponent()->IncreaseMaxhealth(_healthIncreasePercentage);
}

void UUpgrade_IncreaseMaxHealth::UndoAction()
{
	_player->GetHealthComponent()->DecreaseMaxHealth(_healthIncreasePercentage);
}
