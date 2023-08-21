// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileAttack.h"

#include "../Enemies/BaseEnemy.h"

#include "Components/SphereComponent.h"

// Sets default values
AProjectileAttack::AProjectileAttack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	_staticMesh->SetupAttachment(RootComponent);
	_sphereCollider = CreateDefaultSubobject<USphereComponent>(FName("HitCollider"));
	_sphereCollider->SetupAttachment(_staticMesh);

}

void AProjectileAttack::BeginPlay()
{
	Super::BeginPlay();

	if (_sphereCollider)
		_sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectileAttack::OverlapBegin);
}

void AProjectileAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//move projectile forward
	FVector movementVector = GetActorForwardVector() * (_movementSpeed * DeltaTime);
	SetActorLocation(GetActorLocation() + movementVector);
}

void AProjectileAttack::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	auto enemy = Cast<ABaseEnemy>(OtherActor);

	if (enemy == nullptr)
		return;

	OnEnemyHit.Broadcast(this, enemy->GetHealthComponent());
	
	DestroyAttack();
}

