// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_List_PanelWidget.h"

#include "01_Item/ItemType.h"
#include "Engine/DataTable.h"
#include "03_Widget/09_Combination/Combination_List_ButtonWidget.h"
#include "Components/VerticalBox.h"

void UCombination_List_PanelWidget::OnAllEquipment()
{
	VerticalBox_Combination->ClearChildren();

	if(WeaponTable != nullptr)
	{
		for(auto iter : Cast<UDataTable>(WeaponTable)->GetRowNames())
		{
			auto info = Cast<UDataTable>(WeaponTable)->FindRow<FWeapon>(iter, "");
			if (info != nullptr) {
				if (info->item_Code != "item_Equipment_NoWeapon") {
					auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
					if (button != nullptr)
					{
						button->SetItemInfo(info);
						VerticalBox_Combination->AddChild(button);
					}
				}
			}
		}
	}
	if(ArmorTable != nullptr)
	{
		for (auto iter : Cast<UDataTable>(ArmorTable)->GetRowNames())
		{
			auto info = Cast<UDataTable>(ArmorTable)->FindRow<FArmor>(iter, "");
			if (info != nullptr) {
				if (info->item_Code != "item_Equipment_NoArmor" && info->item_Code != "item_Equipment_NoShoes") {
					auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
					if (button != nullptr)
					{
						button->SetItemInfo(info);
						VerticalBox_Combination->AddChild(button);
					}
				}
			}
		}
	}
}

void UCombination_List_PanelWidget::OnWeapon()
{
	VerticalBox_Combination->ClearChildren();

	if (WeaponTable != nullptr)
	{
		for (auto iter : Cast<UDataTable>(WeaponTable)->GetRowNames())
		{
			auto info = Cast<UDataTable>(WeaponTable)->FindRow<FWeapon>(iter, "");
			if (info != nullptr) {
				if (info->item_Code != "item_Equipment_NoWeapon") {
					auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
					if (button != nullptr)
					{
						button->SetItemInfo(info);
						VerticalBox_Combination->AddChild(button);
					}
				}
			}
		}
	}
}

void UCombination_List_PanelWidget::OnArmor()
{
	VerticalBox_Combination->ClearChildren();

	if (ArmorTable != nullptr)
	{
		for (auto iter : Cast<UDataTable>(ArmorTable)->GetRowNames())
		{
			auto info = Cast<UDataTable>(ArmorTable)->FindRow<FArmor>(iter, "");
			if (info != nullptr) {
				if (info->armorType == EArmorType::TOP) {
					if (info->item_Code != "item_Equipment_NoArmor") {
						auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
						if (button != nullptr)
						{
							button->SetItemInfo(info);
							VerticalBox_Combination->AddChild(button);
						}
					}
				}
			}
		}
	}
}

void UCombination_List_PanelWidget::OnShoes()
{
	VerticalBox_Combination->ClearChildren();

	if (ArmorTable != nullptr)
	{
		for (auto iter : Cast<UDataTable>(ArmorTable)->GetRowNames())
		{
			auto info = Cast<UDataTable>(ArmorTable)->FindRow<FArmor>(iter, "");
			if (info != nullptr) {
				if (info->armorType == EArmorType::SHOES) {
					if (info->item_Code != "item_Equipment_NoShoes") {
						auto button = CreateWidget<UCombination_List_ButtonWidget>(GetOwningPlayer(), buttonClass);
						if (button != nullptr)
						{
							button->SetItemInfo(info);
							VerticalBox_Combination->AddChild(button);
						}
					}
				}
			}
		}
	}
}
