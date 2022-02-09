// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_EquipmentWidget/EquipmentPanelWidget.h"

#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/ItemType.h"
#include "Components/VerticalBox.h"
#include "03_Widget/04_EquipmentWidget/EquipmentPartsWidget.h"
#include "03_Widget/04_EquipmentWidget/EquipmentButtonWidget.h"
#include "Components/HorizontalBox.h"

void UEquipmentPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnEquipmentWidget.AddDynamic(this, &UEquipmentPanelWidget::OnEquipmentWidgetEvent);
}

void UEquipmentPanelWidget::OnEquipmentWidgetEvent(UInventoryComponent* inventoryComp, FName equipmentType)
{
	if(equipmentType.IsEqual("Weapon"))
	{
		ShowWeapon(inventoryComp);
	}
	else if(equipmentType.IsEqual("Armor"))
	{
		ShowArmor(inventoryComp);
	}
	else if(equipmentType.IsEqual("Pants"))
	{
		ShowPants(inventoryComp);
	}

}

void UEquipmentPanelWidget::ShowWeapon(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;
	if (inven.Num() > 0) {
		UEquipmentPartsWidget* horizontalBox = nullptr;
		for (auto iter : inven)
		{
			if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT) {
				if (Cast<AItemActor>(iter)->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON) {
					if (index % 6 == 0)
					{
						horizontalBox = CreateWidget<UEquipmentPartsWidget>(GetOwningPlayer(), horizontalBoxClass);
						VerticalBox_Equipment->AddChild(horizontalBox);
					}
					auto button = CreateWidget<UEquipmentButtonWidget>(GetOwningPlayer(), buttonWidgetClass);

					const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
					button->SetUpButton(info);
					button->SetPadding(30);
					button->bIsFocusable = true;

					horizontalBox->GetHorizontalBox_Parts()->AddChild(button);
					//Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

					buttons.Add(button);

					index++;

				}
			}
		}
	}
}

void UEquipmentPanelWidget::ShowArmor(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	if (inven.Num() > 0) {
		UEquipmentPartsWidget* horizontalBox = nullptr;
		for (auto iter : inven)
		{
			if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT) {
				if (Cast<AItemActor>(iter)->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::ARMOR) {
					if (Cast<AItemActor>(iter)->GetItemInfo<FArmor>()->armorType == EArmorType::TOP) {
						if (index % 6 == 0)
						{
							horizontalBox = CreateWidget<UEquipmentPartsWidget>(GetOwningPlayer(), horizontalBoxClass);
							VerticalBox_Equipment->AddChild(horizontalBox);
						}
						auto button = CreateWidget<UEquipmentButtonWidget>(GetOwningPlayer(), buttonWidgetClass);

						const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
						button->SetUpButton(info);
						button->SetPadding(30);
						button->bIsFocusable = true;

						horizontalBox->GetHorizontalBox_Parts()->AddChild(button);
						//Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

						buttons.Add(button);

						index++;

					}
				}
			}
		}
	}
}

void UEquipmentPanelWidget::ShowPants(UInventoryComponent* inventoryComp)
{
	ClearWidget();

	auto inven = inventoryComp->GetItemArray();

	int32 index = 0;

	if (inven.Num() > 0) {
		UEquipmentPartsWidget* horizontalBox = nullptr;
		for (auto iter : inven)
		{
			if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT) {
				if (Cast<AItemActor>(iter)->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::ARMOR) {
					if (Cast<AItemActor>(iter)->GetItemInfo<FArmor>()->armorType == EArmorType::SHOES) {
						if (index % 6 == 0)
						{
							horizontalBox = CreateWidget<UEquipmentPartsWidget>(GetOwningPlayer(), horizontalBoxClass);
							VerticalBox_Equipment->AddChild(horizontalBox);
						}
						auto button = CreateWidget<UEquipmentButtonWidget>(GetOwningPlayer(), buttonWidgetClass);

						const FIteminfo* info = Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>();
						button->SetUpButton(info);
						button->SetPadding(30);
						button->bIsFocusable = true;

						horizontalBox->GetHorizontalBox_Parts()->AddChild(button);
						//Cast<UHorizontalBoxSlot>(button->Slot)->SetSize(ESlateSizeRule::Fill);

						buttons.Add(button);

						index++;

					}
				}
			}
		}
	}
}

void UEquipmentPanelWidget::ClearWidget()
{
	buttons.Empty();
	VerticalBox_Equipment->ClearChildren();
}
