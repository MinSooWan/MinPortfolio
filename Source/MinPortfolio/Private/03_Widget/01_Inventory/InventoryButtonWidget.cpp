// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/Image.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/InventoryComponent.h"

void UInventoryButtonWidget::SetUpButton(const FIteminfo* info)
{
	
	item_info = *info;
	item_code = info->item_Code;
	Image_Item->SetBrushFromTexture(info->item_Image);
	
}

FReply UInventoryButtonWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey("Gamepad_FaceButton_Bottom"))
	{
		GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(item_code);
	}

	return FReply::Handled();
}

FReply UInventoryButtonWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		
		GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(item_code);
	}

	return FReply::Handled();
}

void UInventoryButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
