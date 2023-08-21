// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHud.generated.h"

class UProgressBar;
class UTextBlock;
class APlayerCharacter;
class ALevelManager;

UCLASS()
class MAGE_SURVIVORS_API UPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayer(APlayerCharacter* player);

private:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UProgressBar* _healthBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UProgressBar* _expBar;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _healthPercentageTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _expPercentageTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _playerLevelTextBlock;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _timerTextBlock;

	UPROPERTY()
		APlayerCharacter* _player;
	UPROPERTY()
		ALevelManager* _levelManager;

	//Functions

	UFUNCTION()
		void SetPlayerHealth();
	UFUNCTION()
		void SetExp();
	UFUNCTION()
		void SetCurrentLevel();
	UFUNCTION()
		void SetTime();

 	
};
