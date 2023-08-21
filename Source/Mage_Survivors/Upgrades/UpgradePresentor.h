// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradePresentor.generated.h"

class UUpgrade;
class APlayerCharacter;
class UUpgradeCard;

UCLASS()
class MAGE_SURVIVORS_API AUpgradePresentor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradePresentor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		int _amountOfUpgradesToPresent = 3;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<UUpgrade>> _availableUpgrades;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUpgradeCard> _upgradeCardWidgetClass;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float _borderOffset = 50;

	UPROPERTY()
		APlayerCharacter* _player;
	UPROPERTY()
		UUpgradeCard* _upgradeCard;
	UPROPERTY()
		APlayerController* _playerController;
	UPROPERTY()
		TArray<UUpgrade*> _randomSelectedUpgrade;
	UPROPERTY()
		TArray<UUpgradeCard* >_visibleCards;

	FTimerHandle _findPlayerHandler;
	int32 _screenWidth, _screenHeight;

	//Functions
	
	UFUNCTION()
		void PresentUpgrades();
	UFUNCTION()
		void HandleUpgradeSelected();

	void PauseGame(bool pause);

	UUpgrade* GetRandomUpgrade();

	void SetupUpgradeCards();

	void EnableDisableMouse(bool enable);
};
