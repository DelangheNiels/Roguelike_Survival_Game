// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/BaseCharacter.h"
#include "BaseEnemy.generated.h"

class UDropComponent;
class APlayerCharacter;

UCLASS()
class MAGE_SURVIVORS_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditInstanceOnly)
		UDropComponent* _dropComponent;

private:

	//Variables
	UPROPERTY()
		APlayerCharacter* _player;
	UPROPERTY(EditAnywhere, Category = "Obstacle Detection", meta = (AllowPrivateAccess = "true"))
		float _obstacleDetectionRadius = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Obstacle Detection", meta = (AllowPrivateAccess = "true"))
		float _obstacleDistanceThreshold = 300.0f;
	UPROPERTY(EditAnywhere, Category = "Obstacle Detection", meta = (AllowPrivateAccess = "true"))
		TArray<UClass*> _obstacleClasses;
	UPROPERTY(EditAnywhere, Category = "Obstacle Detection", meta = (AllowPrivateAccess = "true"))
		// Set what actors to seek out from it's collision channel
		TArray<TEnumAsByte<EObjectTypeQuery>> _traceObjectTypes;

	UPROPERTY(EditAnywhere, Category = "Enemy Movement", meta = (AllowPrivateAccess = "true"))
		float _movementSpeed = 280;
	UPROPERTY(EditAnywhere, Category = "Enemy Movement", meta = (AllowPrivateAccess = "true"))
		float _targetDistanceThreshold = 150.0f; //stop moving when closer to the player than this threshold

	UPROPERTY()
		TArray<FVector> _directions;

	//Functions

	UFUNCTION()
		void InstantiateDirections();

	UFUNCTION()
		TArray<AActor*> DetectObstacles(UClass* obstacleClass);

	UFUNCTION()
		TArray<float> AvoidObstacles(TArray<float> danger);

	UFUNCTION()
		float GetWeight(float distanceToObject);

	UFUNCTION()
		TArray<float> SeekPlayer(TArray<float> interest);

	UFUNCTION()
		FVector GetMoveDirection();

	UFUNCTION(BlueprintCallable)
		float GetMovementSpeed();



};
