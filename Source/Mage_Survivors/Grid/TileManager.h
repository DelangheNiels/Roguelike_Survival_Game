// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileManager.generated.h"

class AGridTile;
class APlayerCharacter;

UCLASS()
class MAGE_SURVIVORS_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category ="Info")
		TSubclassOf<AGridTile> _tileObject;
	UPROPERTY(EditAnywhere, Category = "Info")
		float _distanceFromEdgeToSpawnNewTile = 500;
	UPROPERTY(EditAnywhere, Category = "Info")
		int _amountOfTilesActive = 4;

	UPROPERTY()
		TMap<FVector,AGridTile*> _tileMap;
	UPROPERTY()
		TArray<AGridTile*> _activeTiles;

	UPROPERTY()
		AGridTile* _currentPlayerTile;
	UPROPERTY()
		APlayerCharacter* _player;

	//functions
	//------------------------

	void FindPlayer();

	FVector GetPlayerPosOnCurrentTile();

	void ChangeCurrentTile();

	AGridTile* GetClosestTileToPLayer();

	void CheckEdges();

	void CheckCorners();

	bool IsCloseToEdge(float tileDirectionSize, float playerDirectionPos);

	void SpawnNewTile(const FVector& tilePosition);

	bool DoesTileAlreadyExist(const FVector& tilePosition);

	//Set the furthest active tile to inactive to optimize performance
	void HideFurthestTile();

	bool TrySpawningNewTile(bool isCloseToEdge, const FVector& relativeSpawnCoords);
};
