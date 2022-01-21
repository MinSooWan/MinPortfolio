// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/02_Skill/SkillInfoWidget.h"
#include "03_Widget/02_Skill/SkillLearnCheckWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USkillButtonWidget::SetSkillButton(const FSkill* skill_info)
{
	if (skill_info != nullptr) {
		skillInfo = skill_info;
		skill_code = skill_info->skill_code;
		Image_Skill->SetBrushFromTexture(skill_info->skill_icon);
	}
}

void USkillButtonWidget::SkillButtonUp()
{
	if (skillInfo != nullptr) {
		if(skillInfo->needSkills.Num() != 0)
		{
			bool bLearn = false;
			for(auto iter : skillInfo->needSkills)
			{
				for(auto info : GetOwningPlayerPawn<APlayerCharacter>()->GetSkillComp()->GetSkills())
				{
					if(Cast<ASkillBaseActor>(info)->GetSkillInfo<FSkill>()->skill_code.IsEqual(iter))
					{
						bLearn = true;
						break;
					}
					bLearn = false;
				}
				if(bLearn == false)
				{
					break;
				}
			}

			if(bLearn == true)
			{
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->skill_info = skillInfo;
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetVisibility(ESlateVisibility::Visible);
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetFocus();
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("False Skill Learn"));
			}

		}
	}
}

void USkillButtonWidget::SkillButtonHoveredEvent()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->GetButton()->
		WidgetStyle.Normal.SetResourceObject(defaultImage);
	//Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	SetFocus();
	
}

void USkillButtonWidget::SkillButtonUnhoveredEvent()
{
	Button_Skill->WidgetStyle.Normal.SetResourceObject(defaultImage);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->SetFocus();
}

void USkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Skill->OnClicked.AddDynamic(this, &USkillButtonWidget::SkillButtonUp);
	Button_Skill->OnHovered.AddDynamic(this, &USkillButtonWidget::SkillButtonHoveredEvent);
	Button_Skill->OnUnhovered.AddDynamic(this, &USkillButtonWidget::SkillButtonUnhoveredEvent);
}

FReply USkillButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	if (skillInfo != nullptr) {
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillInfoWidget()->SetSkillInfo(skillInfo);
	}
	else
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillInfoWidget()->defaultInfo();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->SetNowButton(this);
	Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	
	return FReply::Handled();
}

void USkillButtonWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	Button_Skill->WidgetStyle.Normal.SetResourceObject(defaultImage);
}

FReply USkillButtonWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetSkillButton()->SetFocus();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right))
	{
		if (Navigation->Right.Widget != nullptr) {
			Navigation->Right.Widget->SetFocus();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left))
	{
		if (Navigation->Left.Widget != nullptr) {
			Navigation->Left.Widget->SetFocus();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down))
	{
		if (Navigation->Down.Widget != nullptr) {
			Navigation->Down.Widget->SetFocus();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up))
	{
		if (Navigation->Up.Widget != nullptr) {
			Navigation->Up.Widget->SetFocus();
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		Button_Skill->OnClicked.Broadcast();
	}

	return FReply::Handled();
}
