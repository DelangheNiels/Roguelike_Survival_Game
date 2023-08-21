// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveManager.h"

#include "../Player/PlayerCharacter.h"
#include "../Objectives/BaseObjective.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AObjectiveManager::AObjectiveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AObjectiveManager::BeginPlay()
{
	Super::BeginPlay();

	auto foundPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (foundPlayer)
		_player = Cast<APlayerCharacter>(foundPlayer);
	
}

void AObjectiveManager::SpawnObjective()
{
	if (_currentAmountInScene >= _totalAllowedAmountInScene || _player == nullptr)
		return;

	int indexOfObjectiveToSpawn = GetRandomObjectiveIndex();
	if (indexOfObjectiveToSpawn < 0)
		return;

	//Calculate random spawn pos
	float xPos = GetRandomCoordinate();
	float yPos = GetRandomCoordinate();

	FVector spawnPos = FVector(xPos, yPos, 0.0f) + _player->GetActorLocation();

	auto objective = GetWorld()->SpawnActor<ABaseObjective>(_spawnableObjectives[indexOfObjectiveToSpawn].Objective, spawnPos, FRotator::ZeroRotator);
	objective->OnObjectiveDestroyed.AddUObject(this, &AObjectiveManager::OnObjectiveDestroyed);

	++_currentAmountInScene;
}

float AObjectiveManager::GetRandomCoordinate()
{
	float randomNumberInRadius = FMath::RandRange(_minDistanceFromPlayer, _maxDistanceFromPlayer);
	int randomPosNeg = FMath::RandRange(-1, 1);

	if (randomPosNeg <= 0)
		randomNumberInRadius *= -1;

	return randomNumberInRadius;
}

int AObjectiveManager::GetRandomObjectiveIndex()
{
	if (_spawnableObjectives.Num() <= 0)
		return -1;

	if (_spawnableObjectives.Num() < 2)
		return 0;

	int index = 0;

	int totalWeight = GetTotalSpawnWeight();

	int randomWeight = FMath::RandRange(0, totalWeight);
	int checkedWeight = 0;
	for (int i = 0; i < _spawnableObjectives.Num(); i++)
	{
		if (randomWeight > checkedWeight && randomWeight <= _spawnableObjectives[i].SpawnWeight)
		{
			index = i;
			break;
		}

		checkedWeight += _spawnableObjectives[i].SpawnWeight;
	}

	return index;
}

int AObjectiveManager::GetTotalSpawnWeight()
{
	int total = 0;

	for (int i = 0; i < _spawnableObjectives.Num(); i++)
	{
		total += _spawnableObjectives[i].SpawnWeight;
	}

	return total;
}

void AObjectiveManager::OnObjectiveDestroyed(ABaseObjective* objective)
{
	objective->OnDestroyed.RemoveAll(objective);
	--_currentAmountInScene;
}


