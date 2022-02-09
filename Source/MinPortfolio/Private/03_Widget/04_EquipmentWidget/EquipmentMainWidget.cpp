// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/04_EquipmentWidget/EquipmentMainWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UEquipmentMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Weapon->OnClicked.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Weapon);
	Button_Armor->OnClicked.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Armor);
	Button_Pants->OnClicked.AddDynamic(this, &UEquipmentMainWidget::OnClickButton_Pants);
}

FReply UEquipmentMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey(EKeys::E) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder))
	{
		if (nowButton->Navigation->Next.Widget != nullptr)
		{
			nowButton->WidgetStyle.Normal.SetResourceObject(normalTexture);
			nowButton->Navigation->Next.Widget->SetFocus();
			nowButton = Cast<UButton>(nowButton->Navigation->Next.Widget.Get());
			nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Q) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder))
	{
		if (nowButton->Navigation->Previous.Widget != nullptr)
		{
			nowButton->WidgetStyle.Normal.SetResourceObject(normalTexture);
			nowButton->Navigation->Previous.Widget->SetFocus();
			nowButton = Cast<UButton>(nowButton->Navigation->Previous.Widget.Get());
			nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetTextBlock_MenuName()->SetText(FText::FromString(TEXT("Menu")));
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->GetEquipmentButton()->SetFocus();
		SetVisibility(ESlateVisibility::Hidden);
	}

	 return FReply::Handled();
}

void UEquipmentMainWidget::WidgetFocus(UButton* widget)
{
}

void UEquipmentMainWidget::OnClickButton_Weapon()
{
}


void UEquipmentMainWidget::OnClickButton_Armor()
{
}

void UEquipmentMainWidget::OnClickButton_Pants()
{
}

void UEquipmentMainWidget::OnEquipmentWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Visible);
	Button_Weapon->SetFocus();
	nowButton = Button_Weapon;
	nowButton->WidgetStyle.Normal.SetResourceObject(hoveredTexture);


}
