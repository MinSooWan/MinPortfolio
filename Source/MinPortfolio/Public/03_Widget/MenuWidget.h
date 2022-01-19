// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		TArray<class UButton*> buttonArray;

	UPROPERTY()
		class UButton* previous_button;
	UPROPERTY()
		class UButton* next_button;
	UPROPERTY()
		class UButton* now_button;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* pressedImage;

	UPROPERTY()
		class UButton* Button_Inventory;
	UPROPERTY()
		class UButton* Button_Skill;
	UPROPERTY()
		class UButton* Button_Equipment;
	UPROPERTY()
		class UButton* Button_Quest;

	UPROPERTY()
		class UImage* Image_Inventory;
	UPROPERTY()
		class UImage* Image_Skill;
	UPROPERTY()
		class UImage* Image_Equipment;
	UPROPERTY()
		class UImage* Image_Quest;

	UPROPERTY()
		class UTextBlock* TextBlock_MenuName;

	UFUNCTION()
		void InventoryClick();
	UFUNCTION()
		void SkillClick();
	UFUNCTION()
		void EquipmentClick();
	UFUNCTION()
		void QuestClick();
	UFUNCTION()
		void InventoryHovered();
	UFUNCTION()
		void SkillHovered();
	UFUNCTION()
		void EquipmentHovered();
	UFUNCTION()
		void QuestHovered();
	UFUNCTION()
		void InventoryUnhovered();
	UFUNCTION()
		void SkillUnhovered();
	UFUNCTION()
		void EquipmentUnhovered();
	UFUNCTION()
		void QuestUnhovered();


	void SetImage(class UImage* widget_image, class UTexture2D* image);

	void pressedNext();
	void pressedPrevious();

public:
	void OnMenuWidget();

	class UButton* GetSkillButton() { return Button_Skill; }
	class UButton* GetEquipmentButton() { return Button_Equipment; }
	class UButton* GetQuestButton() { return Button_Quest; }
	class UButton* GetInventoryButton() { return Button_Inventory; }
	class UTextBlock* GetTextBlock_MenuName() { return TextBlock_MenuName; };

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
