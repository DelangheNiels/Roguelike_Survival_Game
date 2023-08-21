// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHud.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/HealthComponent.h"
#include "../Components/LevelComponent.h"
#include "../Managers/LevelManager.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

bool UPlayerHud::Initialize()
{
	bool success = Super::Initialize();

	if (!success)
		return false;

	auto foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALevelManager::StaticClass());
	if (foundActor)
		_levelManager = Cast<ALevelManager>(foundActor);

	return true;
}

void UPlayerHud::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	SetTime();
}

void UPlayerHud::SetPlayer(APlayerCharacter* player)
{
	if (!player)
		return;

	_player = player;

	SetPlayerHealth();
	SetExp();
	SetCurrentLevel();

	_player->GetHealthComponent()->OnHealthChanged.AddUObject(this, &UPlayerHud::SetPlayerHealth);
	_player->GetLevelComponent()->OnLevelUp.AddUObject(this, &UPlayerHud::SetCurrentLevel);
	_player->GetLevelComponent()->OnGainedEXP.AddUObject(this, &UPlayerHud::SetExp);


}

void UPlayerHud::SetPlayerHealth()
{
	float healthPercentage = _player->GetHealthComponent()->GetHealthPercentage();
	_healthBar->SetPercent(healthPercentage);
	FText healthText = FText::FromString(FString::SanitizeFloat(healthPercentage * 100).Append(" %"));
	_healthPercentageTextBlock->SetText(healthText);
}

void UPlayerHud::SetExp()
{
	float expPercentage = _player->GetLevelComponent()->GetLevelPercentage();
	_expBar->SetPercent(expPercentage);
	FText expText = FText::FromString(FString::SanitizeFloat(expPercentage * 100).Append(" %"));
	_expPercentageTextBlock->SetText(expText);
}

void UPlayerHud::SetCurrentLevel()
{
	int currentLevel = _player->GetLevelComponent()->GetCurrentLevel();
	FText expText = FText::FromString(FString::Printf(TEXT("LV: %i"),currentLevel));
	_playerLevelTextBlock->SetText(expText);
}

void UPlayerHud::SetTime()
{
	if (!_levelManager)
		return;

	FTime playedTime = _levelManager->GetPlayedTime();
	FText timeText = FText::FromString(FString::Printf(TEXT("%i:%i:%i"),playedTime.Hours,playedTime.Minutes,playedTime.Seconds));
	_timerTextBlock->SetText(timeText);
}
