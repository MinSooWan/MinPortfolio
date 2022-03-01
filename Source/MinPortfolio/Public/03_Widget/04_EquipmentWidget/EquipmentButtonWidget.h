// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "01_Item/ItemType.h"
#include "EquipmentButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquipmentButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* equippedImage;

	UPROPERTY()
		class UButton* Button_item;
	UPROPERTY()
		class UImage* Image_Equipment;
	UPROPERTY()
		class UImage* Image_Button;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		FName item_code = NAME_None;

	UPROPERTY()
		class UTextBlock* TextBlock_Equipped;

public:
	UPROPERTY()
		class AItemActor* equipmentItem;

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
	class UImage* GetImage_button() { return Image_Button; };
	class UTexture2D* GetHoveredImage() { return hoveredImage; };
	class UTexture2D* GetDefaultImage() { return defaultImage; }
	class UTexture2D* GetEquippedImage() { return equippedImage; }

	void SetUpButton(class AItemActor* item);

	virtual void NativeConstruct() override;

	class AItemActor* GetEquipmentItem() { return equipmentItem; }

};
