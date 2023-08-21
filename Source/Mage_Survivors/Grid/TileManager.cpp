// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "GridTile.h"

#include "../Player/PlayerCharacter.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	//Spawn first tile at (0,0,0)
	if (_tileObject != nullptr)
	{
		auto tile = GetWorld()->SpawnActor<AGridTile>(_tileObject, FVector::ZeroVector, FRotator::ZeroRotator);
		_currentPlayerTile = tile;
		_tileMap.Add(FVector::ZeroVector, tile);
		_activeTiles.Add(tile);
	}

	FindPlayer();
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckEdges();
	CheckCorners();
	ChangeCurrentTile();
}

void ATileManager::FindPlayer()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), foundActors);

	if (foundActors.Num() > 0)
		_player = Cast<APlayerCharacter>(foundActors[0]);
}

FVector ATileManager::GetPlayerPosOnCurrentTile()
{
	if (_player == nullptr || _currentPlayerTile == nullptr)
		return FVector::ZeroVector;

	return _player->GetActorLocation() - _currentPlayerTile->GetActorLocation();
}

void ATileManager::ChangeCurrentTile()
{
	FVector posOnCurrentTile = GetPlayerPosOnCurrentTile();

	if(FMath::Abs(posOnCurrentTile.X) <= _currentPlayerTile->GetTileLenght() && FMath::Abs(posOnCurrentTile.Y) <= _currentPlayerTile->GetTileWidth())
		return;
	
	//Set the new tile where the player is currently on
	AGridTile* tile = GetClosestTileToPLayer();
	if(tile != nullptr)
		_currentPlayerTile = GetClosestTileToPLayer();
}

AGridTile* ATileManager::GetClosestTileToPLayer()
{
	AGridTile* tile = nullptr;

	for (int i = 0; i < _activeTiles.Num(); i++)
	{
		if (_activeTiles[i] == _currentPlayerTile)
			continue;

		FVector result = _player->GetActorLocation() - _activeTiles[i]->GetActorLocation();

		if (FMath::Abs(result.X) < _activeTiles[i]->GetTileLenght() && FMath::Abs(result.Y) < _activeTiles[i]->GetTileWidth())
		{
			tile = _activeTiles[i];
			return tile;
		}

	}

	return nullptr;
}

void ATileManager::CheckEdges()
{
	FVector playerPosOnTile = GetPlayerPosOnCurrentTile();

	//Top edge
	TrySpawningNewTile(IsCloseToEdge(_currentPlayerTile->GetTileLenght(), playerPosOnTile.X), FVector(_currentPlayerTile->GetTileLenght() * 2, 0, 0));

	//Botttom edge
	TrySpawningNewTile(IsCloseToEdge(-_currentPlayerTile->GetTileLenght(), playerPosOnTile.X), FVector(-_currentPlayerTile->GetTileLenght() * 2, 0, 0));

	//Right edge
	TrySpawningNewTile(IsCloseToEdge(_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(0, _currentPlayerTile->GetTileWidth() * 2, 0));

	//Left edge
	TrySpawningNewTile(IsCloseToEdge(-_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(0, -_currentPlayerTile->GetTileWidth() * 2, 0));
}

void ATileManager::CheckCorners()
{
	FVector playerPosOnTile = GetPlayerPosOnCurrentTile();

	//can return after a true result because it is impossible to be in 2 corners at once

	//Top right corner
	if (TrySpawningNewTile(IsCloseToEdge(_currentPlayerTile->GetTileLenght(), playerPosOnTile.X) && IsCloseToEdge(_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(_currentPlayerTile->GetTileLenght() * 2, _currentPlayerTile->GetTileLenght() * 2, 0)))
		return;

	//Bottom right corner
	if (TrySpawningNewTile(IsCloseToEdge(-_currentPlayerTile->GetTileLenght(), playerPosOnTile.X) && IsCloseToEdge(_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(-_currentPlayerTile->GetTileLenght() * 2, _currentPlayerTile->GetTileLenght() * 2, 0)))
		return;

	//Bottom left corner
	if (TrySpawningNewTile(IsCloseToEdge(-_currentPlayerTile->GetTileLenght(), playerPosOnTile.X) && IsCloseToEdge(-_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(-_currentPlayerTile->GetTileLenght() * 2, -_currentPlayerTile->GetTileLenght() * 2, 0)))
		return;

	//Top left corner
	if (TrySpawningNewTile(IsCloseToEdge(_currentPlayerTile->GetTileLenght(), playerPosOnTile.X) && IsCloseToEdge(-_currentPlayerTile->GetTileWidth(), playerPosOnTile.Y), FVector(_currentPlayerTile->GetTileLenght() * 2, -_currentPlayerTile->GetTileLenght() * 2, 0)))
		return;
}

bool ATileManager::IsCloseToEdge(float tileDirectionSize, float playerDirectionPos)
{
	float distanceFromEdge = tileDirectionSize - playerDirectionPos;
	if (FMath::Abs(distanceFromEdge) < _distanceFromEdgeToSpawnNewTile)
		return true;

	return false;
}

void ATileManager::SpawnNewTile(const FVector& tilePosition)
{
	if (DoesTileAlreadyExist(tilePosition))
	{
		auto tile = _tileMap[tilePosition];
		if (_activeTiles.Contains(tile))
			return;

		//Set tile active
		tile->SetActorHiddenInGame(false);

		//Add to active tiles
		_activeTiles.Add(tile);
	}
	else
	{
		//Spawn new tile
		AGridTile* tile = GetWorld()->SpawnActor<AGridTile>(_tileObject, tilePosition, FRotator::ZeroRotator);
		_tileMap.Add(tilePosition, tile);
		_activeTiles.Add(tile);
	}

	HideFurthestTile();

}

bool ATileManager::DoesTileAlreadyExist(const FVector& tilePosition)
{
	return _tileMap.Contains(tilePosition);
}

void ATileManager::HideFurthestTile()
{
	if (_activeTiles.Num() <= _amountOfTilesActive)
		return;

	//Find tile furthes away from player
	AGridTile* tile = nullptr;
	float furthestDistance = 0;
	for (int i = 0; i < _amountOfTilesActive; i++)
	{
		float distance = FVector::Dist(_player->GetActorLocation(), _activeTiles[i]->GetActorLocation());

		if (distance < furthestDistance)
			continue;

		furthestDistance = distance;
		tile = _activeTiles[i];
	}

	if (tile == nullptr)
		return;

	tile->SetActorHiddenInGame(true);
	_activeTiles.Remove(tile);
	_activeTiles.Shrink();
}

bool ATileManager::TrySpawningNewTile(bool isCloseToEdge, const FVector& relativeSpawnCoords)
{
	if (!isCloseToEdge)
		return false;

	FVector newPos = _currentPlayerTile->GetActorLocation() + relativeSpawnCoords;
	SpawnNewTile(newPos);

	return true;
}

