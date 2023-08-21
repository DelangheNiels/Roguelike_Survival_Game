// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

class AObjectiveManager;
class AEnemyManager;

USTRUCT(BlueprintType)
struct FTime
{
	GENERATED_BODY()

public:

	int Hours;
	int Minutes;
	int Seconds;
};

UCLASS()
class MAGE_SURVIVORS_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		FTime GetPlayedTime();

private:

	//current play time
	float _currentPlayedTime;

	//Enemy spawning
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		AEnemyManager* _enemyManager;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _timeBetweenEnemySpawns = 30.0f;
	float _enemySpawnTimer = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _timeBetweenDifficultyIncrease = 60.0f;
	float _difficultyIncreaseTimer = 0.0f;

	//Objective spawning
	UPROPERTY(EditAnywhere, Category = "Objective Spawning", meta = (AllowPrivateAccess = "true"))
		AObjectiveManager* _objectiveManager;
	UPROPERTY(EditAnywhere, Category = "Objective Spawning", meta = (AllowPrivateAccess = "true"))
		float _timeToStartSpawningObjectives = 180.0f;
	UPROPERTY(EditAnywhere, Category = "Objective Spawning", meta = (AllowPrivateAccess = "true"))
		float _timeBetweenObjectiveSpawns = 60.0f;
	float _objectiveSpawnTimer;

	//Functions
	void TrySpawningObjective(float deltaTime);
	void TrySpawningEnemies(float deltaTime);
	void IncreaseDifficulty(float deltaTime);

};
