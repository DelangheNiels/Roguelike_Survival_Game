// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveProgressBar.generated.h"

class UProgressBar;

DECLARE_MULTICAST_DELEGATE(FOnCompleted);

UCLASS()
class MAGE_SURVIVORS_API UObjectiveProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	void SetFillPercentage(float percentage);

	FOnCompleted OnCompleted;

	UProgressBar* GetProgressBar() const;

private:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UProgressBar* _progressBar;
	
};
