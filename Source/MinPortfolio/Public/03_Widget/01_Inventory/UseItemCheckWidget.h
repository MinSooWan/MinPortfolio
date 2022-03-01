// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UseItemCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UUseItemCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class AItemActor* item;

	UPROPERTY()
		class UButton* nowButton;
	UPROPERTY()
		class UButton* Button_Yes;
	UPROPERTY()
		class UButton* Button_No;

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
		void UseItemEvent();
	UFUNCTION()
		void NotUseItemEvent();

	void ChangeButton();

	void SetItemCode(AItemActor* value) { nowButton = Button_Yes; nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage); item = value; }
};
