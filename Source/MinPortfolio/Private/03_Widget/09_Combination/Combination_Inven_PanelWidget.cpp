// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_Inven_PanelWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/09_Combination/Combination_List_ButtonWidget.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetSystemLibrary.h"

void UCombination_Inven_PanelWidget::OnInvenList(UUserWidget* superButton)
{
	VerticalBox_Inven->ClearChildren();
	if (needInfo != nullptr) {
		if (needCode != "") {
			auto arr = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->GetItemArray();
			if (arr.Num() > 0)
			{
				UKismetSystemLibrary::PrintString(GetOwningPlayer(), needCode.ToString());
				for (auto iter : arr)
				{
					if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Code.IsEqual(needCode))
					{
						auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
						if (button != nullptr)
						{
							button->SetItemInfo(Cast<AItemActor>(iter), superButton);
							VerticalBox_Inven->AddChild(button);
						}
					}
				}
			}
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetOwningPlayer(), "Code Is None");
		}
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetOwningPlayer(), "Info Is None");
	}
}
