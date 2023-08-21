// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseObjective.h"
#include "ExpCrystalObjective.h"

#include "../Components/HealthComponent.h"

AExpCrystalObjective::AExpCrystalObjective()
{
	PrimaryActorTick.bCanEverTick = true;

	_healthComp = CreateDefaultSubobject<UHealthComponent>(FName("Health Comp"));
	
	_dropComponent = CreateDefaultSubobject<UDropComponent>(FName("Drop Comp"));
}

void AExpCrystalObjective::BeginPlay()
{
	Super::BeginPlay();
}

void AExpCrystalObjective::OnObjectiveCompleted()
{
	Super::OnObjectiveCompleted();

	if (_healthComp)
	{
		_healthComp->RemoveAllHealth();
	}
}
