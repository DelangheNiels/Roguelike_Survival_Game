// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "../Enemies/BaseEnemy.h"
#include "../Components/LevelComponent.h"
#include "../Upgrades/UpgradeManager.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	_levelComp = CreateDefaultSubobject<ULevelComponent>(FName("LevelComponent"));
	_upgradeManager = CreateDefaultSubobject<UUpgradeManager>(FName("Upgrade Manager"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_findClosestEnemyTimer += DeltaTime;
	if (_findClosestEnemyTimer >= _findClosestEnemyTime)
	{
		_findClosestEnemyTimer = 0.0f;
		AActor* closestEnemy = FindClosestEnemy();
		FaceActor(closestEnemy);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

ULevelComponent* APlayerCharacter::GetLevelComponent() const
{
	return _levelComp;
}

UHealthComponent* APlayerCharacter::GetHealthComponent() const
{
	return _healthComponent;	
}

UUpgradeManager* APlayerCharacter::GetUpgradeManager() const
{
	return _upgradeManager;
}

void APlayerCharacter::MoveForward(float value)
{
	FVector moveDirection = FVector(1, 0, 0);
	moveDirection.X *= value;
	AddMovementInput(moveDirection);
}

void APlayerCharacter::MoveRight(float value)
{
	FVector moveDirection = FVector(0, 1, 0);
	moveDirection.Y *= value;
	AddMovementInput(moveDirection);
}

AActor* APlayerCharacter::FindClosestEnemy()
{
	// Set what actors to seek out from it's collision channel
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

	// Ignore any specific actors
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);

	// Array of actors that are inside the radius of the sphere
	TArray<AActor*> outActors;

	// Total radius of the sphere
	float radius = _findEnemyRange;

	// Sphere's spawn loccation within the world
	FVector sphereSpawnLocation = GetActorLocation();

	// Class that the sphere should hit against
	UClass* seekClass = ABaseEnemy::StaticClass();
	bool hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, radius, traceObjectTypes, seekClass, ignoreActors, outActors);

	if (hit)
		return outActors[0];

	return nullptr;
}

void APlayerCharacter::FaceActor(AActor* actorToFace)
{
	if (actorToFace == nullptr)
		return;

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), actorToFace->GetActorLocation());
	lookAtRotation.Pitch = 0.0f;
	lookAtRotation.Roll = 0.0f;

	//character mesh is rotated 90° to look forward
	lookAtRotation.Yaw -= 90.0f;

	GetMesh()->SetWorldRotation(lookAtRotation);
}
