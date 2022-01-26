﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/NeedSkillFalseWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UNeedSkillFalseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Ok->OnClicked.AddDynamic(this, &UNeedSkillFalseWidget::OnButton_OkClickEvent);
}

void UNeedSkillFalseWidget::OnNeedSkillFalse(TArray<FName> skill_Names)
{
	SetVisibility(ESlateVisibility::Visible);

	bOnNeedSkillWidget = true;
	FString str = "";
	for(auto iter : skill_Names)
	{
		str += iter.ToString();

		if(iter != skill_Names.Last())
		{
			str += ",";
		}
	}

	str += TEXT("을(를) 배우지 않았습니다.");
	TextBlock_NeedSkill->SetText(FText::FromString(str));
	Button_Ok->SetFocus();
}

void UNeedSkillFalseWidget::OnButton_OkClickEvent()
{
	bOnNeedSkillWidget = false;
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->SetFocus();
}