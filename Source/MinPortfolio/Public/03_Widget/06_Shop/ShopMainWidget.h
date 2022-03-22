// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ShopMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UShopMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_ShopList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UShopButtonWidget> itemButtonClass;

	UPROPERTY()
		class UShopButtonWidget* nowItemButton;
	UPROPERTY()
		class UShopButtonWidget* nextItemButton;
	UPROPERTY()
		class UShopButtonWidget* preItemButton;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemStat;
	UPROPERTY()
		class UTextBlock* TextBlock_Description;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_AddOption;
	UPROPERTY()
		class UImage* Item_Image;

public:

	void OnShopWidget();

	void InitShopItemlist();

	FString GetAddOptionDescription_Material(EAddOptionsType_Material option);
	void SetItemInfo(class AItemActor* value);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void NextItemButton();
	void PreItemButton();
};
