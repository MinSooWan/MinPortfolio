// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforcePanelWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/ItemActor.h"
#include "Components/VerticalBox.h"
#include "03_Widget/07_Reinforce/ReinforcePanelPartsWidget.h"
#include "03_Widget/07_Reinforce/ReinforceButtonWidget.h"
#include "Components/HorizontalBox.h"


void UReinforcePanelWidget::OnInventoryEvent()
{
	ShowEquipment();
}

void UReinforcePanelWidget::ShowEquipment()
{
	ClearWidget();

	auto inven = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->GetItemArray();

	int32 index = 0;

	UReinforcePanelPartsWidget* horizontalBox = nullptr;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT) {
			if (index % 6 == 0)
			{
				horizontalBox = CreateWidget<UReinforcePanelPartsWidget>(GetOwningPlayer(), horizontalBoxClass);
				Vertical_Reinforce->AddChild(horizontalBox);
			}
			auto button = CreateWidget<UReinforceButtonWidget>(GetOwningPlayer(), buttonWidgetClass);

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(Cast<AItemActor>(iter));
			button->SetPadding(30);
			button->bIsFocusable = true;

			horizontalBox->GetHorizontar()->AddChild(button);
			//Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}

void UReinforcePanelWidget::ShowMaterial()
{
	ClearWidget();

	auto inven = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->GetItemArray();

	int32 index = 0;

	UReinforcePanelPartsWidget* horizontalBox = nullptr;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::MATERIAL) {
			if (index % 6 == 0)
			{
				horizontalBox = CreateWidget<UReinforcePanelPartsWidget>(GetOwningPlayer(), horizontalBoxClass);
				Vertical_Reinforce->AddChild(horizontalBox);
			}
			auto button = CreateWidget<UReinforceButtonWidget>(GetOwningPlayer(), buttonWidgetClass);

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(Cast<AItemActor>(iter));
			button->SetPadding(30);
			button->bIsFocusable = true;

			horizontalBox->GetHorizontar()->AddChild(button);
			//Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}

void UReinforcePanelWidget::ClearWidget()
{
	buttons.Empty();
	Vertical_Reinforce->ClearChildren();
}

void UReinforcePanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
