// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHealthChanged);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDied, UHealthComponent*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGE_SURVIVORS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void TakeDamage(float damage);
	UFUNCTION()
	void AddHealth(float health);

	UFUNCTION()
		void RemoveAllHealth();

	UFUNCTION()
		float GetHealthPercentage();

	void IncreaseMaxhealth(float percentage);
	void DecreaseMaxHealth(float percentage);

	FOnDied OnDied;
	FOnHealthChanged OnHealthChanged;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float _maxHealth = 100.0f;
	UPROPERTY(BlueprintReadOnly)
	float _currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool _canBeInvulnerable = false;
	bool _isInvulnerable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float _invulnerabilityTime = 0.5f;
	float _invulnerabilityTimer = 0.0f;

		
};
