// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "01_Item/ItemType.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TArray<class UButton*> typeButtons;

	UPROPERTY()
		class UInventoryButtonWidget* nowItemButton;
	UPROPERTY()
		class UInventoryButtonWidget* previousItemButton;
	UPROPERTY()
		class UInventoryButtonWidget* nextItemButton;

	UPROPERTY()
		class UButton* nowTypeButton;
	UPROPERTY()
		class UButton* previousTypeButton;
	UPROPERTY()
		class UButton* nextTypeButton;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemStat;
	UPROPERTY()
		class UTextBlock* TextBlock_Description;
	UPROPERTY()
		class UTextBlock* TextBlock_AddOption;

	UPROPERTY()
		class UButton* Button_All;
	UPROPERTY()
		class UButton* Button_Equipment;
	UPROPERTY()
		class UButton* Button_Material;
	UPROPERTY()
		class UButton* Button_Tool;
	UPROPERTY()
		class UButton* Button_BattleItem;

	UPROPERTY()
		class UInventoryPanelWidget* UMG_InvnetoryPanel;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void ShowAllEvent();
	UFUNCTION()
		void ShowEquipmentEvent();
	UFUNCTION()
		void ShowMaterialEvent();
	UFUNCTION()
		void ShowToolEvent();
	UFUNCTION()
		void ShowBattleItemEvent();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void SetItemInfo(FIteminfo* info);

	FString GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option);
	FString GetAddOptionDescription_Material(EAddOptionsType_Material option);
	FString GetAddOptionDescription_BattleItem(EAddOptionsType_BattleItem option);
	FString GetAddOptionDescription_RecoveryItem(EAddOptionsType_RecoveryItem option);

	void PressedNextButton_Type();
	void PressedPreviousButton_Type();

	void PressedNextButton_Item();
	void PressedPreviousButton_Item();
};

