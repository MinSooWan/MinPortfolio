// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Shop/NeedGoldCheckWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/06_Shop/ShopBuyCheckWidget.h"
#include "03_Widget/06_Shop/ShopMainWidget.h"
#include "Components/Button.h"

void UNeedGoldCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Yes->OnPressed.AddDynamic(this, &UNeedGoldCheckWidget::YesButtonPressedEvnet);
	Button_Yes->IsFocusable = true;
}

void UNeedGoldCheckWidget::YesButtonPressedEvnet()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_BuyItemCheck()->SetVisibility(ESlateVisibility::Hidden);
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ShopWidget()->SetFocus();
}
