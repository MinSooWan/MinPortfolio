// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/Image.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/01_Inventory/UseItemCheckWidget.h"
#include "Components/Button.h"

void UInventoryButtonWidget::OnPressedEvnet()
{
	Image_button->SetBrushFromTexture(hoveredImage);
}

void UInventoryButtonWidget::OnReleasedEvnet()
{
	//Image_button->SetBrushFromTexture(defaultImage);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetCheckWidget()->SetItemCode(item);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetCheckWidget()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetCheckWidget()->SetFocus();
}

void UInventoryButtonWidget::OnHoveredEvnet()
{
	Image_button->SetBrushFromTexture(hoveredImage);
}

void UInventoryButtonWidget::OnUnhoveredEvent()
{
	Image_button->SetBrushFromTexture(defaultImage);
}

void UInventoryButtonWidget::SetUpButton(AItemActor* value)
{
	//auto temp = info;
	item = value;
	if (item) {
		item_code = item->GetItemInfo<FIteminfo>()->item_Code;
		if (item->GetItemInfo<FIteminfo>()->item_Image != nullptr) {
			Image_Item->SetBrushFromTexture(item->GetItemInfo<FIteminfo>()->item_Image);
			if(value->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
			{
				if (Cast<AEquipmentActor>(item)->GetEquipped() == true)
				{
					Image_button->SetBrushFromTexture(equippedImage);
				}
				else
				{
					Image_button->SetBrushFromTexture(defaultImage);
				}
			}
			else
			{
				Image_button->SetBrushFromTexture(defaultImage);
			}
		}
	}
}

void UInventoryButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_item->OnPressed.AddDynamic(this, &UInventoryButtonWidget::OnPressedEvnet);
	Button_item->OnReleased.AddDynamic(this, &UInventoryButtonWidget::OnReleasedEvnet);
	Button_item->OnHovered.AddDynamic(this, &UInventoryButtonWidget::OnHoveredEvnet);
	Button_item->OnUnhovered.AddDynamic(this, &UInventoryButtonWidget::OnUnhoveredEvent);
}
