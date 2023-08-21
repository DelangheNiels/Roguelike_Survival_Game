// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectivePointer.h"

#include "Components/Image.h"

#include "../Player/PlayerCharacter.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UObjectivePointer::NativeConstruct()
{
	Super::NativeConstruct();

	auto foundActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if (foundActor)
		_player = Cast<APlayerCharacter>(foundActor);


	_playerController = Cast<APlayerController>(_player->GetController());
	_playerController->GetViewportSize(_screenWidth, _screenHeight);
}

void UObjectivePointer::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D screenPos = SetCorrectScreenPosition();
	FaceTarget(screenPos);
	
}

void UObjectivePointer::SetImage(UTexture2D* texture)
{
	_pointerImage->SetBrushFromTexture(texture);
}

void UObjectivePointer::SetObjectivePosition(const FVector& targetPos)
{
	_targetPos = targetPos;
}

void UObjectivePointer::FaceTarget(const FVector2D& screenPos)
{
	FVector playerPos = _player->GetActorLocation();
	FVector pointerPos = FVector(screenPos.X + playerPos.X, screenPos.Y + playerPos.Y,0);

	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(pointerPos, _targetPos);
	
	_pointerImage->SetRenderTransformAngle(lookAtRotation.Yaw);
}

FVector2D UObjectivePointer::SetCorrectScreenPosition()
{
	FVector2D targetPosOnScreen;
	_playerController->ProjectWorldLocationToScreen(_targetPos,targetPosOnScreen,true);

	//When too far away, result is zero vector
	if (targetPosOnScreen.Equals(FVector2D::ZeroVector))
	{
		float distance = FVector::Dist(_targetPos, _player->GetActorLocation());
		targetPosOnScreen = _latestValidTargetScreenPos;
	}
	_latestValidTargetScreenPos = targetPosOnScreen;
	
	int32 screenX = (int32)targetPosOnScreen.X;
	int32 screenY = (int32)targetPosOnScreen.Y;

	//Remove Image when objective is on screen
	bool isOnScreen = screenX >= 0 && screenY >= 0 && screenX < _screenWidth && screenY < _screenHeight;
	SetImageVisability(isOnScreen);


	FVector2D cappedScreenPosition = targetPosOnScreen;
	if (cappedScreenPosition.X <= _distanceFromBorder) cappedScreenPosition.X = _distanceFromBorder;
	if(cappedScreenPosition .X >= _screenWidth - _distanceFromBorder) cappedScreenPosition.X = _screenWidth - _distanceFromBorder;
	if (cappedScreenPosition.Y <= _distanceFromBorder) cappedScreenPosition.Y = _distanceFromBorder;
	if (cappedScreenPosition.Y >= _screenHeight - _distanceFromBorder) cappedScreenPosition.Y = _screenHeight - _distanceFromBorder;

	SetPositionInViewport(cappedScreenPosition);

	return cappedScreenPosition;
	
}

void UObjectivePointer::SetImageVisability(bool isObjectiveOnScreen)
{
	if (isObjectiveOnScreen)
		_pointerImage->SetVisibility(ESlateVisibility::Hidden);
	else
		_pointerImage->SetVisibility(ESlateVisibility::Visible);
}

