// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class UHealthComponent;
class APlayerCharacter;

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseEnemy> EnemyType;
	UPROPERTY(EditAnywhere)
		int SpawnWeight;

	//Override the comparison operator, needed to use in TMap
	bool operator==(const FEnemySpawnInfo& other) const
	{
		return EnemyType == other.EnemyType && SpawnWeight == other.SpawnWeight;
	}
};

FORCEINLINE uint32 GetTypeHash(const FEnemySpawnInfo& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FEnemySpawnInfo));
	return Hash;
};

UCLASS()
class MAGE_SURVIVORS_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TrySpawningEnemies();
	void IncreaseEnemySpawns();

private:

	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		TArray<FEnemySpawnInfo> _spawnableEnemies;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		int _maxAmountOfEnemiesAlive = 30;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _enemySpawnDelay = 0.3f;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _enemySpawnIncreaseModifier = 1.05f;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _minimumSpawnDistanceFromPlayer;
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning", meta = (AllowPrivateAccess = "true"))
		float _maximumSpawnDistanceFromPlayer;
	
	UPROPERTY()
		APlayerCharacter* _player;

	int _amountOfEnemiesAlive;
	float _amountOfEnemiesAliveMultiplier = 1.0f;
	int _currentAmountOfEnemiesAlive;

	FTimerHandle _enemySpawnHandler;

	//Functions

	UFUNCTION()
		void SpawnEnemy();
	UFUNCTION()
		TSubclassOf<class ABaseEnemy> GetEnemyTypeToSpawn();
	UFUNCTION()
		FVector CalculateEnemySpawnPosition();
	UFUNCTION()
		void HandleOnEnemyDied(UHealthComponent* healthComp);

	int GetTotalSpawnWeight();
	float GetRandomCoordinate();
};
