// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Combination/Combination_Mate_ButtonWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/09_Combination/CombinationMainWidget.h"
#include "03_Widget/09_Combination/Combination_Inven_PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombination_Mate_ButtonWidget::SetItemInfo(const FComNeedInfo* info)
{
	TextBlock_Name->SetText(FText::FromName(info->item_Name_Com));
	itemInfo = info;
	need_Code = info->item_Code_Com;
}

void UCombination_Mate_ButtonWidget::SetDefaultImage()
{
	Image_Sel->SetBrushFromTexture(defaultImage);
}

void UCombination_Mate_ButtonWidget::SetHoveredImage()
{
	Image_Sel->SetBrushFromTexture(hoveredImage);
}

void UCombination_Mate_ButtonWidget::ApplyItem(AItemActor* value)
{
	Image_Button->SetBrushFromTexture(applyImage_Button);
	bApplyItem = true;
	apItem = value;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->AddApplyItem(apItem);
}

void UCombination_Mate_ButtonWidget::CancelItem()
{
	Image_Button->SetBrushFromTexture(defaultImage_Button);
	bApplyItem = false;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->RemoveApplyItem(apItem);

}

FReply UCombination_Mate_ButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry,
	const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->SetFocus();

	return FReply::Handled();
}

void UCombination_Mate_ButtonWidget::Pressed_Mate()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetUMG_Combination_Inven_Panel()->needInfo = itemInfo;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetUMG_Combination_Inven_Panel()->needCode = need_Code;
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetUMG_Combination_Inven_Panel()->OnInvenList(this);
}
