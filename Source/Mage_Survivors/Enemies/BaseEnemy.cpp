// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "../Components/HealthComponent.h"
#include "../Components/DropComponent.h"

#include "../Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_dropComponent = CreateDefaultSubobject<UDropComponent>(FName("Drop Component"));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	InstantiateDirections();

	auto foundPlayer = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (foundPlayer)
		_player = Cast<APlayerCharacter>(foundPlayer);
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Face Player
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _player->GetActorLocation());
	lookAtRotation.Pitch = 0.0f;
	lookAtRotation.Roll = 0.0f;
	SetActorRotation(lookAtRotation);

	auto moveDir = GetMoveDirection();
	SetActorLocation(GetActorLocation() + (GetMoveDirection() * DeltaTime * GetCharacterMovement()->MaxWalkSpeed));

}

float ABaseEnemy::GetMovementSpeed()
{
	return (GetMoveDirection() * GetCharacterMovement()->MaxWalkSpeed).SquaredLength();
}

void ABaseEnemy::InstantiateDirections()
{
	_directions.Add(FVector(0, 1, 0).GetSafeNormal());
	_directions.Add(FVector(1, 1, 0).GetSafeNormal());
	_directions.Add(FVector(1, 0, 0).GetSafeNormal());
	_directions.Add(FVector(1, -1, 0).GetSafeNormal());
	_directions.Add(FVector(0, -1, 0).GetSafeNormal());
	_directions.Add(FVector(-1, -1, 0).GetSafeNormal());
	_directions.Add(FVector(-1, 1, 0).GetSafeNormal());
	_directions.Add(FVector(-1, 0, 0).GetSafeNormal());
}

TArray<AActor*> ABaseEnemy::DetectObstacles(UClass* obstacleClass)
{
	// Ignore any specific actors
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);
	ignoreActors.Add(_player);

	TArray<AActor*> outActors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), _obstacleDetectionRadius, _traceObjectTypes, obstacleClass, ignoreActors, outActors);

	return outActors;
}

TArray<float> ABaseEnemy::AvoidObstacles(TArray<float> danger)
{
	TArray<AActor*> detectedObstacles;
	for (int i = 0; i < _obstacleClasses.Num(); i++)
	{
		detectedObstacles += DetectObstacles(_obstacleClasses[i]);
	}

	for (int i = 0; i < detectedObstacles.Num(); i++)
	{
		FVector directionToObstacle = detectedObstacles[i]->GetActorLocation() - GetActorLocation();
		float distanceToObject = directionToObstacle.Length();

		//calculate weight of move vector based on distance enemy and obstacle
		float weight = GetWeight(distanceToObject);

		//Set danger value for each direction
		for (int j = 0; j < _directions.Num(); j++)
		{
			//calculates result for if we want to move to the direction or not
			//the closer the result is to 1, the less we want to move to that direction
			float result = FVector::DotProduct(directionToObstacle.GetSafeNormal(), _directions[j]);

			float dangerValue = result * weight;

			if (dangerValue > danger[j])
				danger[j] = dangerValue;
		}
	}

	return danger;
}

//calculate weight of move vector based on distance enemy and obstacle
float ABaseEnemy::GetWeight(float distanceToObject)
{
	//Value 1 = do not move in this direction

	if (distanceToObject <= _obstacleDistanceThreshold)
		return 1;
	else
		return (_obstacleDetectionRadius - distanceToObject) / _obstacleDetectionRadius;
}

TArray<float> ABaseEnemy::SeekPlayer(TArray<float> interest)
{
	if (!_player)
		return interest;

	//Do nothing when close to player
	if (FVector::Dist(GetActorLocation(), _player->GetActorLocation()) <= _targetDistanceThreshold) //set this to attack range of attack component
		return interest;

	//Find interest directions for moving to the player
	FVector directionToPlayer = _player->GetActorLocation() - GetActorLocation();
	for (int i = 0; i < _directions.Num(); i++)
	{
		float result = FVector::DotProduct(directionToPlayer.GetSafeNormal(), _directions[i]);

		//only take direction > 0
		if (result < 0)
			continue;

		//set interest value if bigger than prev
		if (result > interest[i])
			interest[i] = result;
	}

	return interest;
}

FVector ABaseEnemy::GetMoveDirection()
{
	TArray<float> danger;
	danger.Init(0, _directions.Num());

	TArray<float> interest;
	interest.Init(0, _directions.Num());

	//Get danger and interest values
	danger = AvoidObstacles(danger);
	interest = SeekPlayer(interest);

	//Subtract danger from interest
	//Remove directions we don not want to move to
	for (int i = 0; i < interest.Num(); i++)
	{
		interest[i] = FMath::Clamp(interest[i] - danger[i], 0, 1);
	}

	//Calculate average direction
	FVector movementDirection = FVector::ZeroVector;
	for (int i = 0; i < interest.Num(); i++)
	{
		movementDirection += _directions[i] * interest[i];
	}

	return movementDirection.GetSafeNormal();
}


