// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquipmentMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UTexture2D* normalTexture;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredTexture;

	UPROPERTY()
		class UButton* nowButton;

	UPROPERTY()
		class UButton* Button_Weapon;
	UPROPERTY()
		class UButton* Button_Armor;
	UPROPERTY()
		class UButton* Button_Shoes;

	UPROPERTY()
		class UImage* Image_Weapon;
	UPROPERTY()
		class UImage* Image_Armor;
	UPROPERTY()
		class UImage* Image_Shoes;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel;

	UPROPERTY()
		class UEquipmentPanelWidget* UMG_EquipmentPanel;

	UPROPERTY()
		class UEquipmentButtonWidget* nowItemButton;
	UPROPERTY()
		class UEquipmentButtonWidget* previousItemButton;
	UPROPERTY()
		class UEquipmentButtonWidget* nextItemButton;

	UPROPERTY()
		class UTextBlock* TextBlock_Stat_HP;
	UPROPERTY()
		class UTextBlock* TextBlock_Stat_DEX;
	UPROPERTY()
		class UTextBlock* TextBlock_Stat_DEF;
	UPROPERTY()
		class UTextBlock* TextBlock_Stat_SP;
	UPROPERTY()
		class UTextBlock* TextBlock_Stat_ATC;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void WidgetFocus(class UButton* widget);

	UFUNCTION()
		void OnClickButton_Weapon();
	UFUNCTION()
		void OnClickButton_Armor();
	UFUNCTION()
		void OnClickButton_Shoes();

	void PressedNextButton_Item();
	void PressedPreviousButton_Item();
	void PressedUpButton_Item();
	void PressedDownButton_Item();

public:

	class UImage* GetImage_Weapon() { return Image_Weapon; }
	class UImage* GetImage_Armor() { return Image_Armor; }
	class UImage* GetImage_Shoes() { return Image_Shoes; }

	class UCanvasPanel* GetCanvasPanel() { return CanvasPanel; }

	void OnEquipmentWidget();

	void SetItemImage();
};
