// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLevelUp);
DECLARE_MULTICAST_DELEGATE(FOnGainedEXP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGE_SURVIVORS_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	int GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable)
	float GetLevelPercentage() const;

	void AddEXP(float exp);

	FOnLevelUp OnLevelUp;
	FOnGainedEXP OnGainedEXP;

protected:

	//represents x in: exp = (level * x)^y  
	UPROPERTY(EditAnywhere, Category = "EXP Calculation")
		float _constant;

	//represents y in: exp = (level * x)^y 
	UPROPERTY(EditAnywhere, Category = "EXP Calculation")
		float _power;

private:

	float _currentEXP;
	int _currentLevel;

		
};
