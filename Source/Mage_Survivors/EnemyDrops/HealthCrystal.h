// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDrop.h"
#include "HealthCrystal.generated.h"

/**
 * 
 */
UCLASS()
class MAGE_SURVIVORS_API AHealthCrystal : public ABaseDrop
{
	GENERATED_BODY()

public:

	AHealthCrystal();

protected:

	virtual void BeginPlay() override;

	virtual void OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, Category ="Parameters")
		float _amountToHeal;
	
};
