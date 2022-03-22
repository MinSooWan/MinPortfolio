// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Shop/ShopButtonWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/06_Shop/ShopBuyCheckWidget.h"
#include "03_Widget/06_Shop/ShopMainWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UShopButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	Button_Item->OnPressed.AddDynamic(this, &UShopButtonWidget::OnPressedEvent);
	Button_Item->OnHovered.AddDynamic(this, &UShopButtonWidget::OnHoveredEvent);
	Button_Item->OnUnhovered.AddDynamic(this, &UShopButtonWidget::OnUnhoveredEvent);
}

void UShopButtonWidget::InitButton(AItemActor* value)
{
	if (value != nullptr) {
		TextBlock_ItemNeedGold->SetText(FText::FromString("Gold : " + FString::FromInt(value->GetItemInfo<FIteminfo>()->item_Price)));
		auto text = FText::FromName(value->GetItemInfo<FIteminfo>()->item_Name);
		TextBlock_ItemName->SetText(text);
		Image_Item->SetBrushFromTexture(value->GetItemInfo<FIteminfo>()->item_Image);
		item = value;
	}
}

void UShopButtonWidget::OnPressedEvent()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_BuyItemCheck()->InitCheckWidget(item);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_BuyItemCheck()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_BuyItemCheck()->SetFocus();
}

void UShopButtonWidget::OnHoveredEvent()
{
	Image_Button->SetBrushFromTexture(hoveredImage);
}

void UShopButtonWidget::OnUnhoveredEvent()
{
	Image_Button->SetBrushFromTexture(defaultImage);
}

FReply UShopButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->SetFocus();

	return FReply::Handled();
}
