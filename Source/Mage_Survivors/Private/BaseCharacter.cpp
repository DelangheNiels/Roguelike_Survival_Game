// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "../Enemies/BaseEnemy.h"
#include "../Components/HealthComponent.h"
#include "../Components/AttackComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_healthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComp"));
	_attackComponent = CreateDefaultSubobject<UAttackComponent>(FName("AttackComp"));

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UHealthComponent* ABaseCharacter::GetHealthComponent() const
{
	return _healthComponent;
}

UAttackComponent* ABaseCharacter::GetAttackComponent() const
{
	return _attackComponent;
}

