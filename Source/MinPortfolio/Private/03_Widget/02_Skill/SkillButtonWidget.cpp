// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/02_Skill/SkillInfoWidget.h"
#include "03_Widget/02_Skill/SkillLearnCheckWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USkillButtonWidget::SetSkillButton(const FSkill* skill_info)
{
	skillInfo = skill_info;
	skill_code = skill_info->skill_Name;
	Image_Skill->SetBrushFromTexture(skill_info->skill_icon);
}

void USkillButtonWidget::SkillButtonUp()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->skill_info = skillInfo;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetFocus();
}

void USkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Skill->OnClicked.AddDynamic(this, &USkillButtonWidget::SkillButtonUp);
}

FReply USkillButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillInfoWidget()->SetSkillInfo(skillInfo);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->SetNowButton(this);
	Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	
	return FReply::Handled();
}

void USkillButtonWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	Button_Skill->WidgetStyle.Normal.SetResourceObject(defaultImage);
}
