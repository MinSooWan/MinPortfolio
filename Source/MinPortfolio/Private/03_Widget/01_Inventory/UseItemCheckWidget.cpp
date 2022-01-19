// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/UseItemCheckWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "03_Widget/EquippedItemWidget.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/01_Inventory/InventoryWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UUseItemCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Yes->OnClicked.AddDynamic(this, &UUseItemCheckWidget::UseItemEvent);
	Button_No->OnClicked.AddDynamic(this, &UUseItemCheckWidget::NotUseItemEvent);
}

FReply UUseItemCheckWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right))
	{
		ChangeButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left))
	{
		ChangeButton();
	}
	return FReply::Handled();
}

FReply UUseItemCheckWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		nowButton->OnClicked.Broadcast();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetInventoryWidget()->SetFocus();
	}
	return FReply::Handled();
}

void UUseItemCheckWidget::UseItemEvent()
{
	//UE_LOG(LogTemp, Log, TEXT("UseItem"));

	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(item_code);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetInventoryWidget()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquippedItemWidget()->InitImage();
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
}

void UUseItemCheckWidget::NotUseItemEvent()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetInventoryWidget()->SetFocus();
}

void UUseItemCheckWidget::ChangeButton()
{
	if(nowButton == Button_Yes)
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_No;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
	else
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_Yes;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
}
