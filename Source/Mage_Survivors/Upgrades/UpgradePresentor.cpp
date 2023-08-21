// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradePresentor.h"
#include "Upgrade.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/LevelComponent.h"
#include "../UI/UpgradeCard.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AUpgradePresentor::AUpgradePresentor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AUpgradePresentor::BeginPlay()
{
	Super::BeginPlay();

	auto foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (!foundActor)
		return;

	_player = Cast<APlayerCharacter>(foundActor);
	if (_player)
		_player->GetLevelComponent()->OnLevelUp.AddUObject(this, &AUpgradePresentor::PresentUpgrades);

	_playerController = Cast<APlayerController>(_player->GetController());
	_playerController->GetViewportSize(_screenWidth, _screenHeight);
}

// Called every frame
void AUpgradePresentor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpgradePresentor::PresentUpgrades()
{
	_randomSelectedUpgrade.Empty();

	for (int i = 0; i < _amountOfUpgradesToPresent; i++)
	{
		_randomSelectedUpgrade.Add(GetRandomUpgrade());
	}

	SetupUpgradeCards();
	PauseGame(true);

}

void AUpgradePresentor::HandleUpgradeSelected()
{
	//Remove all upgrade cards from view
	for (int i = 0; i < _visibleCards.Num(); i++)
	{
		UUpgradeCard* card = _visibleCards[i];
		card->OnSelected.RemoveAll(card);
		card->RemoveFromParent();
	}

	_visibleCards.Empty();
	PauseGame(false);
}


void AUpgradePresentor::PauseGame(bool pause)
{
	if (!_playerController)
		return;

	_playerController->SetPause(pause);
	EnableDisableMouse(pause);
}

UUpgrade* AUpgradePresentor::GetRandomUpgrade()
{
	UUpgrade* upgrade;
	do
	{
		int randomIndex = FMath::RandRange(0, _availableUpgrades.Num() - 1);
		upgrade = _availableUpgrades[randomIndex].GetDefaultObject();

	} while (_randomSelectedUpgrade.Contains(upgrade));

	
	return upgrade;
}

void AUpgradePresentor::SetupUpgradeCards()
{
	float offset = (_screenWidth / _amountOfUpgradesToPresent);

	for (int i = 0; i < _randomSelectedUpgrade.Num(); i++)
	{
		UUpgrade* upgrade = _randomSelectedUpgrade[i];
		upgrade->SetPlayer(_player);
		_upgradeCard = Cast<UUpgradeCard>(CreateWidget(GetWorld(), _upgradeCardWidgetClass));
		if (_upgradeCard)
		{
			_upgradeCard->SetUpgradeData(upgrade, _player->GetUpgradeManager());
			_upgradeCard->AddToViewport();

			FVector2D pos = FVector2D((offset * i) + _borderOffset, _screenHeight / 4);

			_upgradeCard->SetPositionInViewport(pos);
			_visibleCards.Add(_upgradeCard);
			_upgradeCard->OnSelected.AddUObject(this, &AUpgradePresentor::HandleUpgradeSelected);
		}
	}

	_randomSelectedUpgrade.Empty();
}

void AUpgradePresentor::EnableDisableMouse(bool enable)
{
	_playerController->bShowMouseCursor = enable;
	_playerController->bEnableClickEvents = enable;
	_playerController->bEnableMouseOverEvents = enable;
}

