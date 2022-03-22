// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UShopButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class AItemActor* item;

	UPROPERTY()
		class UImage* Image_Button;
	UPROPERTY()
		class UImage* Image_Item;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemNeedGold;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;
	UPROPERTY()
		class UButton* Button_Item;
public:
	class AItemActor* GetItem() { return item; }

	virtual void NativeConstruct() override;

	void InitButton(class AItemActor* value);

	UFUNCTION()
		void OnPressedEvent();
	UFUNCTION()
		void OnHoveredEvent();
	UFUNCTION()
		void OnUnhoveredEvent();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
