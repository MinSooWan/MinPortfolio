// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillInfomation.h"
#include "Blueprint/UserWidget.h"
#include "SkillButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

	UPROPERTY()
		class UButton* Button_Skill;
	UPROPERTY()
		class UImage* Image_Skill;
	UPROPERTY()
		FName skill_code;

	UPROPERTY()
		bool bAvailable = false;

public:
	const FSkill* skillInfo;

	void SetSkillButton(const FSkill* skill_info);

	bool GetAvailable() { return bAvailable; }

	class UButton* GetButton() { return Button_Skill; }
	class UImage* GetImage_Skill() { return Image_Skill; }

	UFUNCTION()
		void SkillButtonUp();
	UFUNCTION()
		void SkillButtonHoveredEvent();
	UFUNCTION()
		void SkillButtonUnhoveredEvent();

	virtual void NativeConstruct() override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent);
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void LearnSkill();
	void AvailableSkill();

	void CheckLearnSkill();
	bool CheckNeedSp();

	bool Checking();
	void ReturnFoucs();
};

