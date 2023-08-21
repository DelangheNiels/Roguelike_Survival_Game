// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttack.h"

#include "../Components/HealthComponent.h"

// Sets default values
ABaseAttack::ABaseAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseAttack::DestroyAttack()
{
	OnDestroyed.Broadcast(this);
	Destroy();
}

// Called every frame
void ABaseAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_timeAlive += DeltaTime;
	if (_timeAlive >= _timeToLive)
		DestroyAttack();
}

float ABaseAttack::GetBaseDamage() const
{
	return _baseDamage;
}




