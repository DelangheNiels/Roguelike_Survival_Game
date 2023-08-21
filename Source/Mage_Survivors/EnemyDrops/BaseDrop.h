// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDrop.generated.h"

class USphereComponent;
class USplineComponent;

UCLASS()
class MAGE_SURVIVORS_API ABaseDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseDrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) PURE_VIRTUAL(ABaseDrop::OnPickUp);

public:
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditInstanceOnly, Category = "Parameters")
		UStaticMeshComponent* _staticMesh;
	UPROPERTY(EditInstanceOnly, Category = "Parameters")
		USphereComponent* _sphereCollider;

	UPROPERTY(EditAnywhere, Category = "Drop Spawn Arc settings")
		float _movementSpeed = 800;

private:

	UPROPERTY(EditInstanceOnly)
	USplineComponent* _spline;

	float _distanceAlongSpline = 0.0f;

	void MoveAlongSpline(float DeltaTime);

	void SetupSpline();

};
