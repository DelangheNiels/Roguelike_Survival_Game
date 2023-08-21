// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObjective.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveDestroyed, ABaseObjective*);

class USphereComponent;
class UObjectiveProgressBar;
class UWidgetComponent;
class UObjectivePointer;


UCLASS()
class MAGE_SURVIVORS_API ABaseObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnObjectiveCompleted();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FOnObjectiveDestroyed OnObjectiveDestroyed;

private:

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* _defaultRootComponent;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* _staticMesh;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		USphereComponent* _collisionSphere;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* _progressWidget;


	UPROPERTY()
		UObjectivePointer* _pointerWidget;
	
	UPROPERTY()
		UObjectiveProgressBar* _objectiveProgress;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float _timeToFillProgress = 3.0f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float _despawnTime = 60.0f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UTexture2D* _objectivePointerImage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UObjectivePointer> _pointerWidgetClass;

	float _currentProgressTime = 0.0f;
	float _despawnTimer = 0.0f;

	bool _isPlayerInRange;

	//Functions
	float GetFillPercentage();

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void DestroyObjective();

};
