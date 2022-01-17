// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "01_Item/ItemType.h"
#include "InventoryButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UInventoryButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class UImage* Image_Item;
	UPROPERTY()
		class UImage* Image_button;

	UPROPERTY()
		FName item_code = NAME_None;
	UPROPERTY()
		FIteminfo item_info;
	
public:

	class UImage* GetImage_button() { return Image_button; };
	class UTexture2D* GetHoveredImage() { return hoveredImage; };
	class UTexture2D* GetDefaultImage() { return defaultImage; }

	void SetUpButton(const struct FIteminfo* info);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeConstruct() override;
};
