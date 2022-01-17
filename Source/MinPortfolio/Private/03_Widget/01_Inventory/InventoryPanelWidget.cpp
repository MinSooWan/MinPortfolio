// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryPanelWidget.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/HorizontalBoxSlot.h"

void UInventoryPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnInventory.AddDynamic(this, &UInventoryPanelWidget::OnInventoryEvent);
}

void UInventoryPanelWidget::OnInventoryEvent(UInventoryComponent* inventoryComp)
{
	ShowAll(inventoryComp);
}

void UInventoryPanelWidget::ShowAll(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	UHorizontalBox* horizontalBox;
	for(auto iter : inven)
	{
		if(index % 6 == 0)
		{
			horizontalBox = NewObject<UHorizontalBox>();
			Vertical_Inventory->AddChild(horizontalBox);
		}
		auto button = NewObject<UInventoryButtonWidget>();

		const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
		button->SetUpButton(*info);
		button->SetPadding(30);

		horizontalBox->AddChild(button);
		Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

		buttons.Add(button);

		index++;

	}
}

void UInventoryPanelWidget::ShowEquipment(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	UHorizontalBox* horizontalBox;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT) {
			if (index % 6 == 0)
			{
				horizontalBox = NewObject<UHorizontalBox>();
				Vertical_Inventory->AddChild(horizontalBox);
			}
			auto button = NewObject<UInventoryButtonWidget>();

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(*info);
			button->SetPadding(30);

			horizontalBox->AddChild(button);
			Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}

void UInventoryPanelWidget::ShowMaterial(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	UHorizontalBox* horizontalBox;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::MATERIAL) {
			if (index % 6 == 0)
			{
				horizontalBox = NewObject<UHorizontalBox>();
				Vertical_Inventory->AddChild(horizontalBox);
			}
			auto button = NewObject<UInventoryButtonWidget>();

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(*info);
			button->SetPadding(30);

			horizontalBox->AddChild(button);
			Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}

void UInventoryPanelWidget::ShowTool(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	UHorizontalBox* horizontalBox;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::GATHERING_TOOL) {
			if (index % 6 == 0)
			{
				horizontalBox = NewObject<UHorizontalBox>();
				Vertical_Inventory->AddChild(horizontalBox);
			}
			auto button = NewObject<UInventoryButtonWidget>();

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(*info);
			button->SetPadding(30);

			horizontalBox->AddChild(button);
			Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}

void UInventoryPanelWidget::ShowBattleItem(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	UHorizontalBox* horizontalBox;
	for (auto iter : inven)
	{
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::BATTLE_ITEM) {
			if (index % 6 == 0)
			{
				horizontalBox = NewObject<UHorizontalBox>();
				Vertical_Inventory->AddChild(horizontalBox);
			}
			auto button = NewObject<UInventoryButtonWidget>();

			const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
			button->SetUpButton(*info);
			button->SetPadding(30);

			horizontalBox->AddChild(button);
			Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

			buttons.Add(button);

			index++;

		}
	}
}


void UInventoryPanelWidget::ClearWidget()
{
	buttons.Empty();
	Vertical_Inventory->ClearChildren();
}
