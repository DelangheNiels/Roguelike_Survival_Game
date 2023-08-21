// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class ULevelComponent;
class UUpgradeManager;

UCLASS()
class MAGE_SURVIVORS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ULevelComponent* GetLevelComponent() const;
	UHealthComponent* GetHealthComponent() const;
	UUpgradeManager* GetUpgradeManager() const;

private:

	void MoveForward(float value);
	void MoveRight(float value);

	AActor* FindClosestEnemy();
	void FaceActor(AActor* actorToFace);

protected:

	UPROPERTY(EditAnywhere, Category = "Enemy Targeting")
	float _findEnemyRange = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Enemy Targeting")
	float _findClosestEnemyTime = 2.0f;


private:

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		ULevelComponent* _levelComp;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		UUpgradeManager* _upgradeManager;

	float _findClosestEnemyTimer = 0.0f;
	
};
