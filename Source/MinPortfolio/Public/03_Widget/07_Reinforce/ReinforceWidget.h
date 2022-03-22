// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UReinforceButtonWidget* nowItemButton;
	UPROPERTY()
		class UReinforceButtonWidget* previousItemButton;
	UPROPERTY()
		class UReinforceButtonWidget* nextItemButton;

	UPROPERTY()
		class UCanvasPanel* Canvas_Panel_DefaultInfo;

	//ReinforceEquipmnt
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemStat;
	UPROPERTY()
		class UTextBlock* TextBlock_Description;
	UPROPERTY()
		class UTextBlock* TextBlock_AddOption;
	UPROPERTY()
		class UImage* Item_Image;

	UPROPERTY()
		class UReinforcePanelWidget* UMG_ReinforcePanel;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemType;

	UPROPERTY()
		class UBackgroundBlur* BackgroundBlur_Image;

	UPROPERTY()
		bool bEquipment = false;

	UPROPERTY()
		class AItemActor* equipment;
	UPROPERTY()
		class AItemActor* material;

	UPROPERTY()
		class UReinforceInfoWidget* UMG_ReinforceInfo;

public:
	void ShowEquipmentEvent();
	void ShowMaterialEvent();

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void SetItemInfo(AItemActor* item);

	FString GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option);
	FString GetAddOptionDescription_Material(EAddOptionsType_Material option);
	FString GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option);

	void PressedNextButton_Item();
	void PressedPreviousButton_Item();
	void PressedUpButton_Item();
	void PressedDownButton_Item();

	void OnReinforceWidget();

	class UReinforcePanelWidget* GetInvnetoryPanel() { return UMG_ReinforcePanel; }
	class UReinforceInfoWidget* GetUMG_ReinforceInfo() { return UMG_ReinforceInfo; }
};
