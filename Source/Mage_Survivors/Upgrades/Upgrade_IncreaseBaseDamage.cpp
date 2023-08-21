// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade_IncreaseBaseDamage.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/AttackComponent.h"

UUpgrade_IncreaseBaseDamage::UUpgrade_IncreaseBaseDamage()
{

}

void UUpgrade_IncreaseBaseDamage::DoAction()
{
	_player->GetAttackComponent()->IncreaseDamageMultiplier(_damageIncrease);
}

void UUpgrade_IncreaseBaseDamage::UndoAction()
{
	_player->GetAttackComponent()->DecreaseDamageMultiplier(_damageIncrease);
}
