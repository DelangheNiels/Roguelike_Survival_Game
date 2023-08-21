// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTile.h"

#include "../Player/PlayerCharacter.h"

// Sets default values
AGridTile::AGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_defaultRootComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultRootComponent"));
	SetRootComponent(_defaultRootComponent);

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	_staticMesh->SetupAttachment(GetRootComponent());

}

float AGridTile::GetTileWidth() const
{
	return _staticMesh->Bounds.BoxExtent.Y;
}

float AGridTile::GetTileLenght() const
{
	return _staticMesh->Bounds.BoxExtent.X;
}

// Called when the game starts or when spawned
void AGridTile::BeginPlay()
{
	Super::BeginPlay();
}


