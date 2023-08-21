// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelComponent.h"

// Sets default values for this component's properties
ULevelComponent::ULevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

int ULevelComponent::GetCurrentLevel() const
{
	return _constant * FMath::Sqrt(_currentEXP);
}

float ULevelComponent::GetLevelPercentage() const
{
	float expNeededForNextLevel = FMath::Pow((_currentLevel + 1) / _constant, _power);
	float expNeededForPrevLevel = FMath::Pow((_currentLevel) / _constant, _power);

	float percentage = 0;
	if(_currentLevel > 0)
		percentage = (_currentEXP - expNeededForPrevLevel) / (expNeededForNextLevel - expNeededForPrevLevel);
	else
		percentage = _currentEXP / expNeededForNextLevel;
	
	return percentage;
}

void ULevelComponent::AddEXP(float exp)
{
	_currentEXP += exp;

	//check if this causes the player to level up
	int level = GetCurrentLevel();
	if (level != _currentLevel)
	{
		_currentLevel = level;
		//broadcast that the player leveled up
		OnLevelUp.Broadcast();
	}

	OnGainedEXP.Broadcast();
}


