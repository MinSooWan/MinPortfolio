// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_List_ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_List_ButtonWidget : public UUserWidget
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

	const FIteminfo* itemInfo;

	UPROPERTY()
		UUserWidget* applyButton;

	UPROPERTY()
		AItemActor* item;
public:

	void SetItemInfo(const FIteminfo* info);
	void SetItemInfo(AItemActor* value, UUserWidget* button);

	void SetDefaultImage();
	void SetHoveredImage();

	void OnPressed_List();
	void OnPressed_Inven();

	void UnApplyItem();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
