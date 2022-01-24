// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/02_Skill/NeedSpLackWidget.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UNeedSpLackWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Ok->OnClicked.AddDynamic(this, &UNeedSpLackWidget::OnButton_OkClickEvent);
}

void UNeedSpLackWidget::OnNeedSPLack(int32 sp)
{
	SetVisibility(ESlateVisibility::Visible);
	bOnSpLackWidget = true;
	FString str = TEXT("필요 SP : ") + FString::FromInt(sp);
	TextBlock_NeedSp->SetText(FText::FromString(str));
	Button_Ok->SetFocus();
}

void UNeedSpLackWidget::OnButton_OkClickEvent()
{
	bOnSpLackWidget = false;
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetNowButton()->SetFocus();
}
