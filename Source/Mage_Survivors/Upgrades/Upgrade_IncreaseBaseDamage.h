// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Upgrade_IncreaseBaseDamage.generated.h"

/**
 * 
 */
UCLASS()
class MAGE_SURVIVORS_API UUpgrade_IncreaseBaseDamage : public UUpgrade
{
	GENERATED_BODY()
	
public:
	UUpgrade_IncreaseBaseDamage();

	virtual void DoAction() override;
	virtual void UndoAction() override;

private:
	UPROPERTY(EditAnywhere, Category = "Upgrade data", meta = (AllowAccess = "true"))
		float _damageIncrease = 0.1f; //Percentage to increase damage (between 0 and 1)
};
