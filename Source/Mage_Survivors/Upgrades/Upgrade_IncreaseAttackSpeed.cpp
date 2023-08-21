// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade_IncreaseAttackSpeed.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/AttackComponent.h"

UUpgrade_IncreaseAttackSpeed::UUpgrade_IncreaseAttackSpeed()
{

}

void UUpgrade_IncreaseAttackSpeed::DoAction()
{
	_player->GetAttackComponent()->DecreaseAttackCooldownTime(_attackSpeedIncrease);
}

void UUpgrade_IncreaseAttackSpeed::UndoAction()
{
	_player->GetAttackComponent()->IncreaseAttackCooldownTime(_attackSpeedIncrease);
}
