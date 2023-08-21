// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeManager.generated.h"

class UUpgrade;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGE_SURVIVORS_API UUpgradeManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ExecuteUpgrade(UUpgrade* upgrade);

private:

	UPROPERTY(meta = (AllowPrivateAccess = "true"))
	TArray<UUpgrade*> _appliedUpgrades;
};
