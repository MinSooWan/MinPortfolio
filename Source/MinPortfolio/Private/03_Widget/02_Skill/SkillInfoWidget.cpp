// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillInfoWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USkillInfoWidget::defaultInfo()
{
	Image_skillImage->SetBrushFromTexture(nullptr);
	TextBlock_skillName->SetText(FText::FromString(""));
	TextBlock_skillDescription->SetText(FText::FromString(""));
	TextBlock_needSkill->SetText(FText::FromString(""));
	TextBlock_NeedSp->SetText(FText::FromString(""));
}

void USkillInfoWidget::SetSkillInfo(const FSkill* info)
{
	if (info->needSkills.Num() != 0) {
		FString str = TEXT("필요 스킬 : ");
		for (auto iter : info->needSkills)
		{
			str += iter.ToString();

			if (iter != info->needSkills.Last())
			{
				str += ",";
			}
		}
		TextBlock_needSkill->SetText(FText::FromString(str));
	}
	else
	{
		TextBlock_needSkill->SetText(FText::FromString(""));
	}

	FString str = TEXT("필요 SP : ") + FString::FromInt(info->needSPPoint);
	TextBlock_NeedSp->SetText(FText::FromString(str));
	Image_skillImage->SetBrushFromTexture(info->skill_icon);
	TextBlock_skillName->SetText(FText::FromName(info->skill_Name));
	TextBlock_skillDescription->SetText(FText::FromString(info->skill_description));
}
