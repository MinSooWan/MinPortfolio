// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/Image.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/InventoryComponent.h"
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
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetCheckWidget()->SetItemCode(item_code);
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

void UInventoryButtonWidget::SetUpButton(const FIteminfo* info)
{
	//auto temp = info;
	item_info = const_cast<FIteminfo*>(info);
	item_code = info->item_Code;
	if (info->item_Image != nullptr) {
		Image_Item->SetBrushFromTexture(info->item_Image);
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
