// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../EnemyDrops/BaseDrop.h"
#include "DropComponent.generated.h"

class ABaseDrop;
class UHealthComponent;

USTRUCT(BlueprintType)
struct FDropInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseDrop> dropObject;
	UPROPERTY(EditAnywhere)
		int amount;
	UPROPERTY(EditAnywhere) //chance to drop this item on dead value between 0 and 100
		float dropChance;

	//Override the comparison operator, needed to use in TMap
	bool operator==(const FDropInfo& other) const
	{
		return dropObject == other.dropObject && amount == other.amount;
	}
};

FORCEINLINE uint32 GetTypeHash(const FDropInfo& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FDropInfo));
	return Hash;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGE_SURVIVORS_API UDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDropComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnDrops(UHealthComponent* healthComp);

protected:

	UPROPERTY(EditAnywhere, Category ="Drops")
		TArray<FDropInfo> _dropList;

	UPROPERTY()
		UHealthComponent* _healthComp;
		
};
