// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_List_ButtonWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/09_Combination/CombinationMainWidget.h"
#include "03_Widget/09_Combination/Combination_Mate_PanelWidget.h"
#include "05_Combination/Combination_Mate_ButtonWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombination_List_ButtonWidget::SetItemInfo(const FIteminfo* info)
{
	TextBlock_Name->SetText(FText::FromName(info->item_Name));
	itemInfo = info;
}

void UCombination_List_ButtonWidget::SetItemInfo(AItemActor* value, UUserWidget* button)
{
	applyButton = button;
	TextBlock_Name->SetText(FText::FromName(value->GetItemInfo<FIteminfo>()->item_Name));
	item = value;
}

void UCombination_List_ButtonWidget::SetDefaultImage()
{
	Image_Sel->SetBrushFromTexture(defaultImage);
}

void UCombination_List_ButtonWidget::SetHoveredImage()
{
	Image_Sel->SetBrushFromTexture(hoveredImage);
}

void UCombination_List_ButtonWidget::OnPressed_List()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetCanvasPanel_List()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetCanvasPanel_Mate()->SetVisibility(ESlateVisibility::Visible);

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetUMG_Combination_Mate_Panel()->GetVerticalBox_MateList()->ClearChildren();

	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetUMG_Combination_Mate_Panel()->InitMateList(itemInfo);
}

void UCombination_List_ButtonWidget::OnPressed_Inven()
{
	if(applyButton != nullptr)
	{
		Cast<UCombination_Mate_ButtonWidget>(applyButton)->ApplyItem(item);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);

		UKismetSystemLibrary::PrintString(GetOwningPlayer(),
			FString::FromInt(GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetApplyItemList().Num()));
	}

}

void UCombination_List_ButtonWidget::UnApplyItem()
{
	if (applyButton != nullptr)
	{
		Cast<UCombination_Mate_ButtonWidget>(applyButton)->CancelItem();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->RemoveApplyItem(item);
		
	}
}

FReply UCombination_List_ButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry,
                                                             const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->SetFocus();

	return FReply::Handled();
}
