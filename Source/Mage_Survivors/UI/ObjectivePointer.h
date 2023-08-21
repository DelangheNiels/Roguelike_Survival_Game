// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivePointer.generated.h"

class UImage;
class APlayerCharacter;

UCLASS()
class MAGE_SURVIVORS_API UObjectivePointer : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void NativeConstruct() override;
	
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
		void SetImage(UTexture2D* texture);
	UFUNCTION()
		void SetObjectivePosition(const FVector& targetPos);

private:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"))
		UImage* _pointerImage;

	UPROPERTY()
		FVector _targetPos;

	UPROPERTY()
		APlayerCharacter* _player;

	UPROPERTY()
		APlayerController* _playerController;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float _distanceFromBorder = 100.0f;

	int32 _screenWidth, _screenHeight;

	FVector2D _latestValidTargetScreenPos;

	//Functions
	void FaceTarget(const FVector2D& screenPos);
	FVector2D SetCorrectScreenPosition();
	void SetImageVisability(bool isObjectiveOnScreen);

};

