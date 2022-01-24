// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillInfomation.h"
#include "Blueprint/UserWidget.h"
#include "SkillInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UImage* Image_skillImage;

	UPROPERTY()
		class UTextBlock* TextBlock_skillName;

	UPROPERTY()
		class UTextBlock* TextBlock_skillDescription;

	UPROPERTY()
		class UTextBlock* TextBlock_needSkill;

	UPROPERTY()
		class UTextBlock* TextBlock_NeedSp;

public:

	void defaultInfo();
	void SetSkillInfo(const FSkill* info);
};
