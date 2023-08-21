// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	_currentHealth = _maxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!_isInvulnerable)
		return;

	_invulnerabilityTimer += DeltaTime;
	if (_invulnerabilityTimer >= _invulnerabilityTime)
	{
		_isInvulnerable = false;
		_invulnerabilityTimer = 0.0f;
	}

}

void UHealthComponent::TakeDamage(float damage)
{
	if (damage <= 0 || _isInvulnerable)
		return;

	_currentHealth -= damage;
	OnHealthChanged.Broadcast();

	if(_canBeInvulnerable)
		_isInvulnerable = true;

	if (_currentHealth > 0)
		return;
	
	//Broadcast that owner died when health below 0
	AActor* owner = GetOwner();
	if (owner)
	{
		OnDied.Broadcast(this);
		owner->Destroy();
	}
}

void UHealthComponent::AddHealth(float health)
{
	if (health <= 0)
		return;

	_currentHealth = FMath::Clamp(_currentHealth + health, _currentHealth, _maxHealth);
	OnHealthChanged.Broadcast();
	
}

void UHealthComponent::RemoveAllHealth()
{
	TakeDamage(_currentHealth);
}

float UHealthComponent::GetHealthPercentage()
{
	return _currentHealth / _maxHealth;
}

void UHealthComponent::IncreaseMaxhealth(float percentage)
{
	float increase = _maxHealth * percentage;
	_maxHealth += increase;
	_currentHealth += increase;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT(" current health is: %f"), _currentHealth));
	OnHealthChanged.Broadcast();
}

void UHealthComponent::DecreaseMaxHealth(float percentage)
{
	float increase = _maxHealth * percentage;
	_maxHealth -= increase;
	_currentHealth -= increase;
	OnHealthChanged.Broadcast();
}


