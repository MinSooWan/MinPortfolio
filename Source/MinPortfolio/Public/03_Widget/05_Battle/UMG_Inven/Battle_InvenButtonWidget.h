// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle_InvenButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UBattle_InvenButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class AItemActor* item;

	UPROPERTY()
		class UImage* Image_Item;

	UPROPERTY()
		class UImage* Image_Button;

	UPROPERTY()
		class UTextBlock* TextBlock_ItemNeedCp;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY()
		class UTextBlock* TextBlock_ItemDec;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

public:
	virtual void NativeConstruct() override;

	void InitButton(class AItemActor* value);

	class AItemActor* GetSkill() { return item; }

	void OnPressedEvent();
	void OnHoveredEvent();
	void OnUnhoveredEvent();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
};
