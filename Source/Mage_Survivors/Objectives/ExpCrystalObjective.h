// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseObjective.h"
#include "ExpCrystalObjective.generated.h"

class UHealthComponent;
class UDropComponent;

UCLASS()
class MAGE_SURVIVORS_API AExpCrystalObjective : public ABaseObjective
{
	GENERATED_BODY()

public:
	AExpCrystalObjective();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnObjectiveCompleted() override;

private:

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* _healthComp;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		UDropComponent* _dropComponent;

};
