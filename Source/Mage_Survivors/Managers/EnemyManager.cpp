// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "../Components/HealthComponent.h"
#include "../Enemies/BaseEnemy.h"
#include "../Player/PlayerCharacter.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	auto foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (foundActor)
		_player = Cast<APlayerCharacter>(foundActor);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::TrySpawningEnemies()
{
	if (_currentAmountOfEnemiesAlive >= _maxAmountOfEnemiesAlive)
		return;

	GetWorldTimerManager().SetTimer(_enemySpawnHandler, this, &AEnemyManager::SpawnEnemy, _enemySpawnDelay, true, 0);
}

void AEnemyManager::IncreaseEnemySpawns()
{
	_maxAmountOfEnemiesAlive *= _enemySpawnIncreaseModifier;
}

void AEnemyManager::SpawnEnemy()
{
	if (_currentAmountOfEnemiesAlive == _maxAmountOfEnemiesAlive)
	{
		GetWorldTimerManager().ClearTimer(_enemySpawnHandler);
		return;
	}

	TSubclassOf<ABaseEnemy> enemyType = GetEnemyTypeToSpawn();
	FVector spawnPosition = CalculateEnemySpawnPosition();
	auto spawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(enemyType, spawnPosition, FRotator::ZeroRotator);

	if (spawnedEnemy == nullptr)
		return;
		
	spawnedEnemy->GetHealthComponent()->OnDied.AddUObject(this, &AEnemyManager::HandleOnEnemyDied);

	++_currentAmountOfEnemiesAlive;
}

TSubclassOf<class ABaseEnemy> AEnemyManager::GetEnemyTypeToSpawn()
{
	TSubclassOf<class ABaseEnemy> enemyType;

	int totalWeight = GetTotalSpawnWeight();

	int randomWeight = FMath::RandRange(0, totalWeight);
	int checkedWeight = 0;
	for (int i = 0; i < _spawnableEnemies.Num(); i++)
	{
		FEnemySpawnInfo spawnInfo = _spawnableEnemies[i];

		if (randomWeight > checkedWeight && randomWeight <= spawnInfo.SpawnWeight)
		{
			enemyType = spawnInfo.EnemyType;
			break;
		}

		checkedWeight += spawnInfo.SpawnWeight;
	}

	return enemyType;
}

FVector AEnemyManager::CalculateEnemySpawnPosition()
{
	FVector playerPos = _player->GetActorLocation();

	float xPos = GetRandomCoordinate();
	float yPos = GetRandomCoordinate();

	return FVector(xPos + playerPos.X, yPos + playerPos.Y, 0.0f);
}

void AEnemyManager::HandleOnEnemyDied(UHealthComponent* healthComp)
{
	healthComp->OnDied.RemoveAll(healthComp);

	--_currentAmountOfEnemiesAlive;
}

int AEnemyManager::GetTotalSpawnWeight()
{
	int total = 0;

	for (int i = 0; i < _spawnableEnemies.Num(); i++)
	{
		total += _spawnableEnemies[i].SpawnWeight;
	}

	return total;
}

float AEnemyManager::GetRandomCoordinate()
{
	float randomNumberInRadius = FMath::RandRange(_minimumSpawnDistanceFromPlayer, _maximumSpawnDistanceFromPlayer);
	int randomPosNeg = FMath::RandRange(-1, 1);

	if (randomPosNeg <= 0)
		randomNumberInRadius *= -1;

	return randomNumberInRadius;
}

