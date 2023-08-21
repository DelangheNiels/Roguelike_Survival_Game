// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Upgrade.generated.h"

class APlayerCharacter;

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class MAGE_SURVIVORS_API UUpgrade : public UObject
{
	GENERATED_BODY()
	
public:
	UUpgrade();

	virtual void DoAction() PURE_VIRTUAL(UUpgrade::DoAction,);
	virtual void UndoAction() PURE_VIRTUAL(UUpgrade::UndoAction);

	void SetPlayer(APlayerCharacter* player);

	FText GetTitle() const;
	FText GetDescription() const;
	UTexture2D* GetImage() const;

protected:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FText _title;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FText _description;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UTexture2D* _image;

	UPROPERTY()
		APlayerCharacter* _player;

};
