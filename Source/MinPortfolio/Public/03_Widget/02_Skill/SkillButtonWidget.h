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

	const FSkill* skillInfo;

public:
	void SetSkillButton(const FSkill* skill_info);

	UFUNCTION()
		void SkillButtonUp();

	virtual void NativeConstruct() override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent);
};

