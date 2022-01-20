// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/SkillLearnCheckWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "Components/Button.h"
#include "04_Skill/SkillBaseActor.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"

void USkillLearnCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnClicked.AddDynamic(this, &USkillLearnCheckWidget::OnClickButton_Yes);
	Button_No->OnClicked.AddDynamic(this, &USkillLearnCheckWidget::OnClickButton_No);
}

void USkillLearnCheckWidget::ChangeNowButton()
{
	nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
	if(nowButton == Button_Yes)
	{
		nowButton = Button_No;
	}
	else
	{
		nowButton = Button_Yes;
	}

	nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
}

void USkillLearnCheckWidget::OnClickButton_Yes()
{
	auto spawnskill = GetWorld()->SpawnActor<ASkillBaseActor>(skill_info->skillActorClass);
	GetOwningPlayerPawn<APlayerCharacter>()->GetSkillComp()->AddSkill(spawnskill);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void USkillLearnCheckWidget::OnClickButton_No()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetRootButton();
}

FReply USkillLearnCheckWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	nowButton = Button_Yes;
	nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);

	return FReply::Handled();
}

FReply USkillLearnCheckWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right))
	{
		ChangeNowButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left))
	{
		ChangeNowButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		nowButton->OnClicked.Broadcast();
	}

	return FReply::Handled();
}
