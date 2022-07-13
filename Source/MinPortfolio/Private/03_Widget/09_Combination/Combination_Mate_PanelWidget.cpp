// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_Mate_PanelWidget.h"

#include "Components/VerticalBox.h"
#include "05_Combination/Combination_Mate_ButtonWidget.h"

void UCombination_Mate_PanelWidget::InitMateList(const FIteminfo* value)
{
	for (auto iter : value->needItems) {
		auto button = CreateWidget<UCombination_Mate_ButtonWidget>(GetOwningPlayer(), ButtonClass);
		if (button != nullptr)
		{
			button->SetItemInfo(&iter);
			VerticalBox_MateList->AddChild(button);
		}
	}
}

bool UCombination_Mate_PanelWidget::AllApItem()
{
	for(auto iter : VerticalBox_MateList->GetAllChildren())
	{
		if(Cast<UCombination_Mate_ButtonWidget>(iter)->GetApplyItem() == false)
		{
			return false;
		}
	}
	return true;
}
