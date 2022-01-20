// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillTreeWidget.h"

#include "03_Widget/02_Skill/SkillButtonWidget.h"

void USkillTreeWidget::GetSkillInfo_Attack(FName skill_name, USkillButtonWidget* widget)
{
	if(SkillAttackTable != nullptr)
	{
		auto info = SkillAttackTable->FindRow<FSkill>(skill_name,"");
		if(info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
	
}

void USkillTreeWidget::GetSkillInfo_Effect(FName skill_name, USkillButtonWidget* widget)
{
	if (SkillAttackTable != nullptr)
	{
		auto info = SkillAttackTable->FindRow<FSkill>(skill_name, "");
		if (info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}

void USkillTreeWidget::GetSkillInfo_Heal(FName skill_name, USkillButtonWidget* widget)
{
	if (SkillAttackTable != nullptr)
	{
		auto info = SkillAttackTable->FindRow<FSkill>(skill_name, "");
		if (info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}

void USkillTreeWidget::GetSkillInfo_Passive(FName skill_name, USkillButtonWidget* widget)
{
	if(SkillAttackTable != nullptr)
	{
		auto info = SkillAttackTable->FindRow<FSkill>(skill_name,"");
		if(info != nullptr)
		{
			widget->SetSkillButton(info);
		}
	}
}
