// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeCard.generated.h"

class UTextBlock;
class UImage;
class UButton;
class UUpgrade;
class UUpgradeManager;

DECLARE_MULTICAST_DELEGATE(FOnSelected);

UCLASS()
class MAGE_SURVIVORS_API UUpgradeCard : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetUpgradeData(UUpgrade* upgrade, UUpgradeManager* upgradeManager);

	FOnSelected OnSelected;

private:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _titleText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UTextBlock* _descriptionText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UImage* _image;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UButton* _button;

	UPROPERTY()
		UUpgrade* _upgrade;
	UPROPERTY()
		UUpgradeManager* _upgradeManager;

	//Functions

	void SetImage(UTexture2D* image);
	void SetDescriptionText(FText text);
	void SetTitle(FText text);

	UFUNCTION()
		void OnUpgradeSelected();
	
};
