// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_Inven_PanelWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/09_Combination/Combination_List_ButtonWidget.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombination_Inven_PanelWidget::OnInvenList(FName code)
{
	VerticalBox_Inven->ClearChildren();
	auto arr = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->GetItemArray();
	if(arr.Num() > 0)
	{
		for(auto iter : arr)
		{
			if(Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Code.IsEqual(code))
			{
				//UKismetSystemLibrary::PrintString(GetOwningPlayer(), "equal code");
				auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
				if(button != nullptr)
				{
					button->SetItemInfo(Cast<AItemActor>(iter), button);
					VerticalBox_Inven->AddChild(button);
				}
			}
		}
	}
}
