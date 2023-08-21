// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

class ABaseAttack;
class UArrowComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGE_SURVIVORS_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void IncreaseDamageMultiplier(float value);
	void DecreaseDamageMultiplier(float value);

	void DecreaseAttackCooldownTime(float value);
	void IncreaseAttackCooldownTime(float value);

	UFUNCTION()
	void DealDamage(ABaseAttack* attack, UHealthComponent* healthComp);

	UFUNCTION()
	void HandleAttackDestroyed(ABaseAttack* attack);

private:

	void SpawnAttack();

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ABaseAttack> _attackObject;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float _attackCooldownTime = 1.0f;
	float _attackCooldownTimer = 0.0f;

	bool _canAttack;

	float _damageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float _attackRange = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UClass* _classToHit;

	UPROPERTY()
	UArrowComponent* _attackSpawnLocation;

private:
	TArray<AActor*> _actorsToIgnore;
	TArray<AActor*> _actorsHit;

		
};
