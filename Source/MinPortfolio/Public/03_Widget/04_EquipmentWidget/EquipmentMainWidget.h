// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquipmentMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UTexture2D* normalTexture;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredTexture;

	UPROPERTY()
		class UButton* nowButton;

	UPROPERTY()
		class UButton* Button_Weapon;
	UPROPERTY()
		class UButton* Button_Armor;
	UPROPERTY()
		class UButton* Button_Pants;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void WidgetFocus(class UButton* widget);

	void OnClickButton_Weapon();
	void OnClickButton_Armor();
	void OnClickButton_Pants();

public:

	void OnEquipmentWidget();
};
