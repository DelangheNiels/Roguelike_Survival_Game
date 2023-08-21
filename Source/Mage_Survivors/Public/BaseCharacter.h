// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UAttackComponent;

UCLASS()
class MAGE_SURVIVORS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		UHealthComponent* GetHealthComponent() const;
	UFUNCTION(BlueprintCallable)
		UAttackComponent* GetAttackComponent() const;

protected:

	UPROPERTY(EditInstanceOnly, Category = "Health")
		UHealthComponent* _healthComponent;
	UPROPERTY(EditInstanceOnly, Category = "Attack")
		UAttackComponent* _attackComponent;
};
