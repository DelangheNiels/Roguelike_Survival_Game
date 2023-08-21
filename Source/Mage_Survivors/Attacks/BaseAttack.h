// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAttack.generated.h"

class UHealthComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnemyHit, ABaseAttack*, UHealthComponent*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDestroyed, ABaseAttack*);

UCLASS()
class MAGE_SURVIVORS_API ABaseAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DestroyAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnEnemyHit OnEnemyHit;
	FOnDestroyed OnDestroyed;

	float GetBaseDamage() const;

protected:

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float _baseDamage = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float _timeToLive = 1.0f;
	float _timeAlive = 0.0f;
};
