// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDrop.h"
#include "ExpCrystal.generated.h"

/**
 * 
 */
UCLASS()
class MAGE_SURVIVORS_API AExpCrystal : public ABaseDrop
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExpCrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:

	UPROPERTY(EditAnywhere, Category ="Drop Info")
	float _expToGive;
	
};
