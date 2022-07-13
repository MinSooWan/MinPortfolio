// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_Mate_ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_Mate_ButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage_Button;
	UPROPERTY(EditAnywhere)
		class UTexture2D* applyImage_Button;

	UPROPERTY()
		class UImage* Image_Sel;
	UPROPERTY()
		class UTextBlock* TextBlock_Name;

	const FComNeedInfo* itemInfo;

	FName need_Code;

	UPROPERTY()
		class UImage* Image_Button;

	UPROPERTY()
		bool bApplyItem = false;

	UPROPERTY()
		class AItemActor* apItem;
public:
	void SetItemInfo(const FComNeedInfo* info);

	void SetDefaultImage();
	void SetHoveredImage();

	void ApplyItem(class AItemActor* value);
	void CancelItem();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	void Pressed_Mate();

	bool GetApplyItem() { return bApplyItem; }
};
