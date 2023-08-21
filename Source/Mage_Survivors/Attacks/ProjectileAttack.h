// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttack.h"
#include "ProjectileAttack.generated.h"

class USphereComponent;

UCLASS()
class MAGE_SURVIVORS_API AProjectileAttack : public ABaseAttack
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AProjectileAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Attack Settings")
	float _movementSpeed = 30.0f;

	UPROPERTY(EditInstanceOnly, Category = "Projectile")
	UStaticMeshComponent* _staticMesh;
	UPROPERTY(EditInstanceOnly, Category = "Projectile")
	USphereComponent* _sphereCollider;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
