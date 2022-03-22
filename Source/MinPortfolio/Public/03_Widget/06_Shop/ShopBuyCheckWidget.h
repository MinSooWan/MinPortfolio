// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopBuyCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UShopBuyCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class AItemActor* item;

	UPROPERTY()
		class UButton* Button_Yes;

	UPROPERTY()
		class UButton* Button_No;

	UPROPERTY()
		class UButton* nowButton;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void InitCheckWidget(class AItemActor* value);

	void ChangeButton();

	UFUNCTION()
		void YesButtonPressedEvent();
	UFUNCTION()
		void NoButtonPressedEvent();
};
