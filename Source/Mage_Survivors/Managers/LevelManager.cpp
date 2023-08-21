// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "ObjectiveManager.h"
#include "EnemyManager.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	//makes it so the first objective spawns immedialtly when it is possible
	_objectiveSpawnTimer = _timeBetweenEnemySpawns;
	_enemySpawnTimer = _timeBetweenEnemySpawns;
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_currentPlayedTime += DeltaTime;

	TrySpawningObjective(DeltaTime);
	TrySpawningEnemies(DeltaTime);
	IncreaseDifficulty(DeltaTime);

}

FTime ALevelManager::GetPlayedTime()
{
	float remainder = _currentPlayedTime;
	float hours, minutes;
	FTime time;

	hours = _currentPlayedTime / 3600.0f;
	time.Hours = int(hours);
	remainder = hours - time.Hours;

	minutes = remainder * 60.0f;
	time.Minutes = int(minutes);
	remainder = minutes - time.Minutes;

	time.Seconds = remainder * 60;

	return time;
}

void ALevelManager::TrySpawningObjective(float deltaTme)
{
	if (_currentPlayedTime < _timeToStartSpawningObjectives || _objectiveManager == nullptr)
		return;

	_objectiveSpawnTimer += deltaTme;

	if (_objectiveSpawnTimer >= _timeBetweenObjectiveSpawns)
	{
		_objectiveSpawnTimer = 0.0f;
		_objectiveManager->SpawnObjective();
	}

}

void ALevelManager::TrySpawningEnemies(float deltaTime)
{
	if (!_enemyManager)
		return;

	_enemySpawnTimer += deltaTime;
	if (_enemySpawnTimer >= _timeBetweenEnemySpawns)
	{
		_enemyManager->TrySpawningEnemies();
		_enemySpawnTimer = 0.0f;
	}
}

void ALevelManager::IncreaseDifficulty(float deltaTime)
{
	if (!_enemyManager)
		return;

	_difficultyIncreaseTimer += deltaTime;
	if (_difficultyIncreaseTimer >= _timeBetweenDifficultyIncrease)
	{
		_enemyManager->IncreaseEnemySpawns();
		_difficultyIncreaseTimer = 0;
	}
}

