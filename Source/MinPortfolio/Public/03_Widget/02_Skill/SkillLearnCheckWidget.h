// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillInfomation.h"
#include "Blueprint/UserWidget.h"
#include "SkillLearnCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillLearnCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class UButton* nowButton;
	UPROPERTY()
		class UButton* Button_Yes;
	UPROPERTY()
		class UButton* Button_No;

	UPROPERTY()
		class USkillButtonWidget* targetWidget;

	UPROPERTY()
		bool bOnLearnWidget = false;
public:
	bool GetOnLearnWidget() { return bOnLearnWidget; }

	void SetTargetWidget(class USkillButtonWidget* target) { targetWidget = target; }

	const FSkill* skill_info;
	virtual void NativeConstruct() override;

	void ChangeNowButton();

	UFUNCTION()
		void OnClickButton_Yes();
	UFUNCTION()
		void OnClickButton_No();

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
