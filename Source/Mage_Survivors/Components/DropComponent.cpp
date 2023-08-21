// Fill out your copyright notice in the Description page of Project Settings.


#include "DropComponent.h"

#include "../EnemyDrops/BaseDrop.h"

#include "../Components/HealthComponent.h"


// Sets default values for this component's properties
UDropComponent::UDropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDropComponent::BeginPlay()
{
	Super::BeginPlay();

	_healthComp = GetOwner()->GetComponentByClass<UHealthComponent>();

	if (_healthComp)
		_healthComp->OnDied.AddUObject(this, &UDropComponent::SpawnDrops);
	
}

void UDropComponent::SpawnDrops(UHealthComponent* healthComp)
{
	for (int i = 0; i < _dropList.Num(); i++)
	{
		int randomNumber = FMath::RandRange(0, 100);

		if (randomNumber > _dropList[i].dropChance)
			continue;

		for (int j = 0; j < _dropList[i].amount; j++)
		{
			GetWorld()->SpawnActor<ABaseDrop>(_dropList[i].dropObject, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		}
		
	}

	_healthComp->OnDied.RemoveAll(this);
}


