// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCrystal.h"

#include "../Player/PlayerCharacter.h"

#include "../Components/HealthComponent.h"

AHealthCrystal::AHealthCrystal()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHealthCrystal::BeginPlay()
{
	Super::BeginPlay();
}

void AHealthCrystal::OnPickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player == nullptr)
		return;

	player->GetHealthComponent()->AddHealth(_amountToHeal);

	Destroy();
}
