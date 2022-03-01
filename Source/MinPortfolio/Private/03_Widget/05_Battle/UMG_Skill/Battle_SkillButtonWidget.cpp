// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillMainWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "04_Skill/SkillInfomation.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UBattle_SkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	
}

void UBattle_SkillButtonWidget::InitButton(ASkillBaseActor* value)
{
	if (value != nullptr) {
		TextBlock_SkillNeedAp->SetText(FText::FromString("AP : " + FString::FromInt(value->GetSkillInfo<FSkill>()->needAP)));
		auto text = FText::FromName(value->GetSkillInfo<FSkill>()->skill_Name);
		TextBlock_SkillName->SetText(text);
		TextBlock_SkillDec->SetText(FText::FromString(value->GetSkillInfo<FSkill>()->skill_description));
		Image_Skill->SetBrushFromTexture(value->GetSkillInfo<FSkill>()->skill_icon);
		skill = value;
	}
}

void UBattle_SkillButtonWidget::OnPressedEvent()
{
	auto owner = GetOwningPlayerPawn<APlayerCharacter>();

	if(owner != nullptr)
	{
		GetOwningPlayer<ABattleController>()->GetMainWidget()->GetUMG_BattleSkillMain()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeGameOnly());
		SetUserFocus(GetOwningPlayer());

		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);

		owner->ActionChange_Impossible();

		owner->GetSkillComp()->UseSkill(skill->GetSkillInfo<FSkill>()->skill_code);

		owner->ActionChange_Impossible();
	}
}

void UBattle_SkillButtonWidget::OnHoveredEvent()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UBattle_SkillButtonWidget::OnUnhoveredEvent()
{
	Image_Button->SetBrushFromTexture(defaultImage);
}

FReply UBattle_SkillButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
	GetOwningPlayer<ABattleController>()->GetMainWidget()->GetUMG_BattleSkillMain()->SetFocus();

	return FReply::Handled();
}
