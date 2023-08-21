// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "HealthComponent.h"

#include "../Enemies/BaseEnemy.h"
#include "../Attacks/BaseAttack.h"
#include "../Attacks/ProjectileAttack.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_canAttack = true;
}

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();	

	_actorsToIgnore.Add(GetOwner());

	auto arrowComps = GetOwner()->GetComponentsByTag(UArrowComponent::StaticClass(), FName("AttackSpawnLocation"));
	if (arrowComps.Num() > 0)
		_attackSpawnLocation = Cast<UArrowComponent>(arrowComps[0]);
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SpawnAttack();

	if (_canAttack)
		return;

	_attackCooldownTimer += DeltaTime;

	if (_attackCooldownTimer >= _attackCooldownTime)
		_canAttack = true;
}

//Increases the damage multiplier of the attack
//value is calculated in percentage between 0 and 1
void UAttackComponent::IncreaseDamageMultiplier(float value)
{
	_damageMultiplier += value;
}

//Decreases the damage multiplier of the attack
//value is calculated in percentage between 0 and 1
void UAttackComponent::DecreaseDamageMultiplier(float value)
{
	_damageMultiplier -= value;
}

//Decreases the cooldown timer of the attack making it so the attack happens more often
void UAttackComponent::DecreaseAttackCooldownTime(float value)
{
	//Clamp so it does not go under 0
	_attackCooldownTime = FMath::Clamp(_attackCooldownTime - value, 0, _attackCooldownTime);
}

void UAttackComponent::IncreaseAttackCooldownTime(float value)
{
	_attackCooldownTime += value;
}

//Only spawns attack when target is in range and attack can spawn
void UAttackComponent::SpawnAttack()
{
	if (!_canAttack || _attackObject == nullptr)
		return;

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

	FVector sphereSpawnLocation = GetOwner()->GetActorLocation();

	bool hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), sphereSpawnLocation, _attackRange, traceObjectTypes, _classToHit, _actorsToIgnore, _actorsHit);

	if (!hit)
		return;

	FActorSpawnParameters SpawnInfo;
	auto spawnedAttack = GetWorld()->SpawnActor<AActor>(_attackObject, GetOwner()->GetActorLocation(), _attackSpawnLocation->GetComponentRotation());
	_canAttack = false;
	_attackCooldownTimer = 0.0f;
	
	ABaseAttack* baseAttack = Cast<ABaseAttack>(spawnedAttack);

	baseAttack->OnEnemyHit.AddUObject(this,&UAttackComponent::DealDamage);
	baseAttack->OnDestroyed.AddUObject(this, &UAttackComponent::HandleAttackDestroyed);
}

void UAttackComponent::DealDamage(ABaseAttack* attack, UHealthComponent* healthComp)
{
	if(healthComp)
		healthComp->TakeDamage(attack->GetBaseDamage() * _damageMultiplier);
}

void UAttackComponent::HandleAttackDestroyed(ABaseAttack* attack)
{
	//Remove all delegetes
	attack->OnEnemyHit.RemoveAll(attack);
}

