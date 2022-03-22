// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Shop/ShopBuyCheckWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/02_NPC/NPCCharacter.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/06_Shop/NeedGoldCheckWidget.h"
#include "03_Widget/06_Shop/ShopMainWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UShopBuyCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnPressed.AddDynamic(this, &UShopBuyCheckWidget::YesButtonPressedEvent);
	Button_No->OnPressed.AddDynamic(this, &UShopBuyCheckWidget::NoButtonPressedEvent);
	bIsFocusable = true;
}

FReply UShopBuyCheckWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Right) || InKeyEvent.GetKey() == FKey(EKeys::E))
	{
		ChangeButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Left) || InKeyEvent.GetKey() == FKey(EKeys::Q))
	{
		ChangeButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		nowButton->OnPressed.Broadcast();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right) || InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->SetFocus();
		SetVisibility(ESlateVisibility::Hidden);
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}

void UShopBuyCheckWidget::InitCheckWidget(AItemActor* value)
{
	nowButton = Button_Yes;
	nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	item = value;
}

void UShopBuyCheckWidget::ChangeButton()
{
	if(nowButton == Button_Yes)
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_No;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
	else if(nowButton == Button_No)
	{
		nowButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
		nowButton = Button_Yes;
		nowButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
	}
}

void UShopBuyCheckWidget::YesButtonPressedEvent()
{
	if(GetOwningPlayerPawn<APlayerCharacter>()->GetMyGold() >= item->GetItemInfo<FIteminfo>()->item_Price)
	{
		GetOwningPlayerPawn<APlayerCharacter>()->SetMyGold(GetOwningPlayerPawn<APlayerCharacter>()->GetMyGold() - item->GetItemInfo<FIteminfo>()->item_Price);
		GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->AddItem(item);
		if(GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->ShopItemList.Contains(item))
		{
			GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->ShopItemList.Remove(item);
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetOwningPlayer(), "false");
		}

		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->InitShopItemlist();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->SetFocus();
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_NeedGoldCheck()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_NeedGoldCheck()->GetButton_Yes()->SetFocus();
	}
}

void UShopBuyCheckWidget::NoButtonPressedEvent()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->SetFocus();
	SetVisibility(ESlateVisibility::Hidden);
}
