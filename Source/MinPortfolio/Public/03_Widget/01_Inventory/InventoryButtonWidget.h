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
		class UButton* Button_item;
	UPROPERTY()
		class UImage* Image_Item;
	UPROPERTY()
		class UImage* Image_button;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FName item_code = NAME_None;

public:
	FIteminfo* item_info;

	UFUNCTION()
		void OnPressedEvnet();
	UFUNCTION()
		void OnReleasedEvnet();
	UFUNCTION()
		void OnHoveredEvnet();
	UFUNCTION()
		void OnUnhoveredEvent();

	//FIteminfo* GetButtonItemInfo() { return *item_info; }
	class UButton* GetButton_item() { return Button_item; }
	class UImage* GetImage_button() { return Image_button; };
	class UTexture2D* GetHoveredImage() { return hoveredImage; };
	class UTexture2D* GetDefaultImage() { return defaultImage; }

	void SetUpButton(const struct FIteminfo* info);

	virtual void NativeConstruct() override;

};
