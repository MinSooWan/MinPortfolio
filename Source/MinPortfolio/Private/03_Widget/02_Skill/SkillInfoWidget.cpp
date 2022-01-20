// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USkillInfoWidget::defaultInfo()
{
	Image_skillImage->SetBrushFromTexture(nullptr);
	TextBlock_skillName->SetText(FText::FromString(""));
	TextBlock_skillDescription->SetText(FText::FromString(""));
}

void USkillInfoWidget::SetSkillInfo(const FSkill* info)
{
	Image_skillImage->SetBrushFromTexture(info->skill_icon);
	TextBlock_skillName->SetText(FText::FromName(info->skill_Name));
	TextBlock_skillDescription->SetText(FText::FromString(info->skill_description));
}
