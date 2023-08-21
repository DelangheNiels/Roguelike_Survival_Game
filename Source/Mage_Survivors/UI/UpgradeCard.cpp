// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeCard.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "../Upgrades/Upgrade.h"
#include "../Upgrades/UpgradeManager.h"
#include "../Player/PlayerCharacter.h"

void UUpgradeCard::NativeConstruct()
{
	Super::NativeConstruct();
	_button->OnClicked.AddDynamic(this, &UUpgradeCard::OnUpgradeSelected);
}

void UUpgradeCard::SetUpgradeData(UUpgrade* upgrade, UUpgradeManager* upgradeManager)
{
	SetImage(upgrade->GetImage());
	SetDescriptionText(upgrade->GetDescription());
	SetTitle(upgrade->GetTitle());

	_upgrade = upgrade;
	_upgradeManager = upgradeManager;
}

void UUpgradeCard::SetImage(UTexture2D* image)
{
	_image->SetBrushFromTexture(image);
}

void UUpgradeCard::SetDescriptionText(FText text)
{
	_descriptionText->SetText(text);
}

void UUpgradeCard::SetTitle(FText text)
{
	_titleText->SetText(text);
}

void UUpgradeCard::OnUpgradeSelected()
{
	//sent upgrade to players upgrade manager
	if (!_upgrade || !_upgradeManager)
		return;

	_upgradeManager->ExecuteUpgrade(_upgrade);
	OnSelected.Broadcast();
}

