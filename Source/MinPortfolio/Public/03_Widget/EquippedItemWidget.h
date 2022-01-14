// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquippedItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquippedItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UImage* Image_Tool;
	UPROPERTY()
		class UImage* Image_Weapon;

	virtual void NativeConstruct() override;

	void InitImage();
};
