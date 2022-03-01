// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/03_KeyImage/KeySettingWidget.h"

#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "Components/CanvasPanel.h"

void UKeySettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CanvasPanel_Menu->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Skill->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Inven->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Equipment->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_Battle->SetVisibility(ESlateVisibility::Hidden);

	if(GetOwningPlayer()->IsA<ABattleController>())
	{
		CanvasPanel_Main->SetVisibility(ESlateVisibility::Hidden);
		//CanvasPanel_Battle->SetVisibility(ESlateVisibility::Visible);
	}
}
