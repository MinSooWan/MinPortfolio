// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_Able_OptionButton.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_Able_OptionButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class UImage* Image_Sel;
	UPROPERTY()
		class UTextBlock* TextBlock_Name;

	UPROPERTY()
		EAddOptionsType_Material addOption;

	UPROPERTY()
		bool bApplyOption = false;

	UPROPERTY()
		class UImage* Image_backG;

	UPROPERTY(EditAnywhere)
		class UTexture2D* applyImage;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage_apply;
public:
	void SetButtonOption(EAddOptionsType_Material value);

	void OnHoveredButton();
	void UnHoveredButton();

	void ApplyOption();
	void UnApplyOption();

	FString GetAddOptionDescription_Material(EAddOptionsType_Material option);

	EAddOptionsType_Material GetAddOption() { return addOption; }

	bool GetIsApplyOption() { return bApplyOption; }
};
