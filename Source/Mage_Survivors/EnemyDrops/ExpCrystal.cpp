// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpCrystal.h"

#include "../Player/PlayerCharacter.h"
#include "../Components/LevelComponent.h"

AExpCrystal::AExpCrystal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExpCrystal::BeginPlay()
{
	Super::BeginPlay();
}

void AExpCrystal::OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player == nullptr)
		return;

	player->GetLevelComponent()->AddEXP(_expToGive);

	Destroy();
}

