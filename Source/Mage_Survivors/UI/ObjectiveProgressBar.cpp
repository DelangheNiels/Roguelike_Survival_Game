// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveProgressBar.h"

#include "Components/ProgressBar.h"

bool UObjectiveProgressBar::Initialize()
{
	bool success = Super::Initialize();

	return success;
}

void UObjectiveProgressBar::SetFillPercentage(float percentage)
{
	_progressBar->SetPercent(percentage);

	if (_progressBar->GetPercent() >= 1)
		OnCompleted.Broadcast();

}

UProgressBar* UObjectiveProgressBar::GetProgressBar() const
{
	return _progressBar;
}
