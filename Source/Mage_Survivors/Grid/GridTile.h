// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

UCLASS()
class MAGE_SURVIVORS_API AGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTile();

	//Y value of box extend
	float GetTileWidth() const;
	//X value of box extend
	float GetTileLenght() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* _defaultRootComponent;

	UPROPERTY(EditInstanceOnly, meta =(AllowPrivateAccess = "true"))
		UStaticMeshComponent* _staticMesh;

};
