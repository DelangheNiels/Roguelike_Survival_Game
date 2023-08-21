// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Upgrade_IncreaseAttackSpeed.generated.h"

UCLASS()
class MAGE_SURVIVORS_API UUpgrade_IncreaseAttackSpeed : public UUpgrade
{
	GENERATED_BODY()
	
public:
	UUpgrade_IncreaseAttackSpeed();

	virtual void DoAction() override;
	virtual void UndoAction() override;

private:
	UPROPERTY(EditAnywhere, Category = "Upgrade data", meta = (AllowAccess = "true"))
		float _attackSpeedIncrease = 0.1f; //(between 0 and 1)
};
