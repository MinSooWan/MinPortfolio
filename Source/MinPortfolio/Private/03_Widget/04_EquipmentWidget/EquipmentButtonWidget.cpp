// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_EquipmentWidget/EquipmentButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemType.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/01_Inventory/UseItemCheckWidget.h"
#include "03_Widget/04_EquipmentWidget/EquipmentMainWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"

void UEquipmentButtonWidget::OnPressedEvnet()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UEquipmentButtonWidget::OnReleasedEvnet()
{
	//Image_button->SetBrushFromTexture(defaultImage);
	GetOwningPlayer<ACustomController>()->GetPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(item_code);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->GetCanvasPanel()->SetVisibility(ESlateVisibility::Hidden);
}

void UEquipmentButtonWidget::OnHoveredEvnet()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UEquipmentButtonWidget::OnUnhoveredEvent()
{
	Image_Button->SetBrushFromTexture(defaultImage);
}

void UEquipmentButtonWidget::SetUpButton(const FIteminfo* info)
{
	//auto temp = info;
	item_info = const_cast<FIteminfo*>(info);
	item_code = info->item_Code;
	if (info->item_Image != nullptr) {
		Image_Equipment->SetBrushFromTexture(info->item_Image);
	}

}

void UEquipmentButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_item->OnPressed.AddDynamic(this, &UEquipmentButtonWidget::OnPressedEvnet);
	Button_item->OnReleased.AddDynamic(this, &UEquipmentButtonWidget::OnReleasedEvnet);
	Button_item->OnHovered.AddDynamic(this, &UEquipmentButtonWidget::OnHoveredEvnet);
	Button_item->OnUnhovered.AddDynamic(this, &UEquipmentButtonWidget::OnUnhoveredEvent);
}
