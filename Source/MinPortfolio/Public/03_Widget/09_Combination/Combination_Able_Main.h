// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_Able_Main.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_Able_Main : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UTextBlock* TextBlock_ItemStat;

	UPROPERTY()
		class UVerticalBox* VerticalBox_AddOption;

	UPROPERTY()
		class UImage* item_image;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCombination_Able_OptionButton> buttonClass;

public:
	void OnComAbleWidget(const FIteminfo* info);

	class UVerticalBox* GetVerticalBox_AddOption() { return  VerticalBox_AddOption; }

	bool IsWeaponAddOption(EAddOptionsType_Material option);
	bool IsArmorAddOption(EAddOptionsType_Material option);
};
