// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillTreeWidget.h"

#include "03_Widget/02_Skill/SkillButtonWidget.h"

void USkillTreeWidget::GetSkillInfo_Attack(FName skill_code, USkillButtonWidget* widget)
{
	if(SkillAttackTable != nullptr)
	{
		auto info = SkillAttackTable->FindRow<FSkill>(skill_code,"");
		if(info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
	
}

void USkillTreeWidget::GetSkillInfo_Effect(FName skill_code, USkillButtonWidget* widget)
{
	if (SkillEffectTable != nullptr)
	{
		auto info = SkillEffectTable->FindRow<FSkill>(skill_code, "");
		if (info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}

void USkillTreeWidget::GetSkillInfo_Heal(FName skill_code, USkillButtonWidget* widget)
{
	if (SkillHealTable != nullptr)
	{
		auto info = SkillHealTable->FindRow<FSkill>(skill_code, "");
		if (info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}

void USkillTreeWidget::GetSkillInfo_Passive(FName skill_code, USkillButtonWidget* widget)
{
	if(SkillPassiveTable != nullptr)
	{
		auto info = SkillPassiveTable->FindRow<FSkill>(skill_code,"");
		if(info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}
