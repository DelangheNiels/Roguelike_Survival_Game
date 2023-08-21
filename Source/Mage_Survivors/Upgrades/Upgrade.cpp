// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrade.h"

#include "../Player/PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

UUpgrade::UUpgrade()
{
}

void UUpgrade::SetPlayer(APlayerCharacter* player)
{
	_player = player;
}	


FText UUpgrade::GetTitle() const
{
	return _title;
}

FText UUpgrade::GetDescription() const
{
	return _description;
}

UTexture2D* UUpgrade::GetImage() const
{
	return _image;
}

