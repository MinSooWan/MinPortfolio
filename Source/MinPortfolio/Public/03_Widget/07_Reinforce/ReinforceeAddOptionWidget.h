// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceeAddOptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceeAddOptionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UTextBlock* TextBlock_AddOption;

	UPROPERTY()
		class UImage* Image_Button;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* selectImage;

	UPROPERTY()
		bool bSelect = false;

	UPROPERTY()
		bool bIsWeapon = false;

	UPROPERTY()
		EAddOptionsType_Equipment addOption_Armor;
	UPROPERTY()
		EAddOptionsType_Equipment_Weapon addOption_Weapon;
public:
	bool GetSelect() { return bSelect; }
	void SetSelect(bool value) { bSelect = value; }

	bool GetIsWeapon() { return bIsWeapon; }
	void SetIsWeapon(bool value) { bIsWeapon = value; }

	void SetDefaultImage();
	void SetHoveredImage();
	void SetSelectImage();

	void SetAddOptionText(FString str);

	EAddOptionsType_Equipment GetAddOption_Armor() { return addOption_Armor; }
	void SetAddOption_Armor(EAddOptionsType_Equipment value) { addOption_Armor = value; }

	EAddOptionsType_Equipment_Weapon GetAddOption_Weapon() { return addOption_Weapon; }
	void SetAddOption_Weapon(EAddOptionsType_Equipment_Weapon value) { addOption_Weapon = value; }

	class UTextBlock* GetTextBlock_AddOption() { return TextBlock_AddOption; }
};
