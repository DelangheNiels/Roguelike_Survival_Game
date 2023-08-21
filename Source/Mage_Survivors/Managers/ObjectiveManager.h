// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveManager.generated.h"

class APlayerCharacter;

USTRUCT(BlueprintType)
struct FObjectiveSpawnInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseObjective> Objective;
	UPROPERTY(EditAnywhere) //chance to drop this item on dead value between 0 and 100
		int SpawnWeight;

	//Override the comparison operator, needed to use in TMap
	bool operator==(const FObjectiveSpawnInfo& other) const
	{
		return Objective == other.Objective && SpawnWeight == other.SpawnWeight;
	}
};



UCLASS()
class MAGE_SURVIVORS_API AObjectiveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void SpawnObjective();

private:

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		int _totalAllowedAmountInScene = 5;
	int _currentAmountInScene = 0;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float _minDistanceFromPlayer = 2000;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		float _maxDistanceFromPlayer = 4000;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (AllowPrivateAccess = "true"))
		TArray<FObjectiveSpawnInfo> _spawnableObjectives;

	APlayerCharacter* _player;

	//Functions

	float GetRandomCoordinate();
	int GetRandomObjectiveIndex();
	int GetTotalSpawnWeight();

	UFUNCTION()
		void OnObjectiveDestroyed(class ABaseObjective* objective);
	
};
