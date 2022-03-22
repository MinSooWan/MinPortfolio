// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceButtonWidget : public UUserWidget
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
		class UImage* Image_Item;
	UPROPERTY()
		class UImage* Image_button;

	UPROPERTY()
		class AItemActor* item;

public:

	UFUNCTION()
		void OnPressedEvnet();
	UFUNCTION()
		void OnHoveredEvnet();
	UFUNCTION()
		void OnUnhoveredEvent();

	class UButton* GetButton_item() { return Button_item; }
	class UImage* GetImage_button() { return Image_button; };
	class UTexture2D* GetHoveredImage() { return hoveredImage; };
	class UTexture2D* GetDefaultImage() { return defaultImage; }
	class UTexture2D* GetEquippedImage() { return equippedImage; }

	void SetUpButton(class AItemActor* value);

	virtual void NativeConstruct() override;

	AItemActor* GetItem() { return item; }
};
