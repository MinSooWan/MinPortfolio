// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/02_Skill/NeedSkillFalseWidget.h"
#include "03_Widget/02_Skill/NeedSpLackWidget.h"
#include "03_Widget/02_Skill/SkillInfoWidget.h"
#include "03_Widget/02_Skill/SkillLearnCheckWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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
		if (Checking() == false) {
			if (bAvailable == false) {
				CheckLearnSkill();
			}
		}
		else
		{
			ReturnFoucs();
		}
	}
}

void USkillButtonWidget::SkillButtonHoveredEvent()
{
	if (Checking() == false) {
		if (GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton() != this) {
			if (GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->GetAvailable() == false) {
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->GetButton()->
					WidgetStyle.Normal.SetResourceObject(defaultImage);
			}
		}
		//Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
		SetFocus();
	}
}

void USkillButtonWidget::SkillButtonUnhoveredEvent()
{
	if (Checking() == false) {
		if (bAvailable == false) {
			Button_Skill->WidgetStyle.Normal.SetResourceObject(defaultImage);
		}
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->SetFocus();
	}
}

void USkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Skill->OnClicked.AddDynamic(this, &USkillButtonWidget::SkillButtonUp);
	Button_Skill->OnHovered.AddDynamic(this, &USkillButtonWidget::SkillButtonHoveredEvent);
	Button_Skill->OnUnhovered.AddDynamic(this, &USkillButtonWidget::SkillButtonUnhoveredEvent);

	if (GetOwningPlayer()->IsA<ACustomController>()) {
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetButtons().Add(this);
	}
}

FReply USkillButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	if (Checking() == false) {
		if (skillInfo != nullptr) {
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillInfoWidget()->SetSkillInfo(skillInfo);
		}
		else
		{
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillInfoWidget()->defaultInfo();
		}

		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->SetNowButton(this);

		if (bAvailable == false) {
			Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
		}
	}
	else
	{
		ReturnFoucs();
	}
	return FReply::Handled();
}

void USkillButtonWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	if (bAvailable == false) {
		Button_Skill->WidgetStyle.Normal.SetResourceObject(defaultImage);
	}
}

FReply USkillButtonWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetSkillButton()->SetFocus();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffSkillTree();
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
	else if(InKeyEvent.GetKey() == FKey(EKeys::W))
	{
		if (Navigation->Up.Widget != nullptr) {
			Navigation->Up.Widget->SetFocus();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::A))
	{
		if (Navigation->Left.Widget != nullptr) {
			Navigation->Left.Widget->SetFocus();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::D))
	{
		if (Navigation->Right.Widget != nullptr) {
			Navigation->Right.Widget->SetFocus();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::S))
	{
		if (Navigation->Down.Widget != nullptr) {
			Navigation->Down.Widget->SetFocus();
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetSkillButton()->SetFocus();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffSkillTree();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		Button_Skill->OnClicked.Broadcast();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}

void USkillButtonWidget::LearnSkill()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->skill_info = skillInfo;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetTargetWidget(this);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetFocus();
}

void USkillButtonWidget::AvailableSkill()
{
	bAvailable = true;
	Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->AddSP(skillInfo->needSPPoint * -1);
}

void USkillButtonWidget::CheckLearnSkill()
{
	if (skillInfo->needSkills.Num() != 0)
	{
		//필요한 스킬의 이름을 구함
		bool bLearn = true;
		FName needSkillName = NAME_None;
		TArray<FName> needSkillNames = skillInfo->needSkills;
		for (auto iter : skillInfo->needSkills)
		{
			if (GetOwningPlayerPawn<APlayerCharacter>()->GetSkillComp()->GetSkillInfos().Contains(iter))
			{
				needSkillNames.Remove(iter);
			}
			else
			{
				bLearn = false;
			}
		}

		//필요한 스킬들을 전부 가지고 있는지
		if (bLearn == true)
		{
			//스킬을 배울 때 소비하는 SP가 있는지
			if (CheckNeedSp()) {
				LearnSkill();
				return;
			}
			else
			{
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSPLack()->OnNeedSPLack(skillInfo->needSPPoint);
			}
		}
		else
		{
			GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSkillFalse()->OnNeedSkillFalse(needSkillNames);
			return;
		}

	}

	if (CheckNeedSp()) {
		LearnSkill();
	}
	else
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSPLack()->OnNeedSPLack(skillInfo->needSPPoint);
	}
}

bool USkillButtonWidget::CheckNeedSp()
{
	if (skillInfo->needSPPoint <= GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetCharacterStat().SkillPoint)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool USkillButtonWidget::Checking()
{
	if(GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->GetOnLearnWidget() != false)
	{
		return true;
	}
	if(GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSkillFalse()->GetOnNeedSkillWidget() != false)
	{
		return true;
	}
	if(GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSPLack()->GetOnSpLackWidget() != false)
	{
		return true;
	}

	return false;
}

void USkillButtonWidget::ReturnFoucs()
{
	if (GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->GetOnLearnWidget() != false)
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillLearnCheck()->SetFocus();
		return;
	}
	if (GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSkillFalse()->GetOnNeedSkillWidget() != false)
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSkillFalse()->GetButton_Ok()->SetFocus();
		return;
	}
	if (GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSPLack()->GetOnSpLackWidget() != false)
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetNeedSPLack()->GetButton_Ok()->SetFocus();
		return;
	}
}

void USkillButtonWidget::NormalAvailableSkill()
{
	bAvailable = true;
	Button_Skill->WidgetStyle.Normal.SetResourceObject(hoveredImage);
}
