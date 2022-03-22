// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/06_Shop/ShopMainWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/02_NPC/NPCCharacter.h"
#include "01_Item/ItemActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/06_Shop/ShopButtonWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UShopMainWidget::OnShopWidget()
{
	UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnShop();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Visible);
	SetFocus();
	InitShopItemlist();
}

void UShopMainWidget::InitShopItemlist()
{
	VerticalBox_ShopList->ClearChildren();
	for(auto iter : GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->ShopItemList)
	{
		auto button = CreateWidget<UShopButtonWidget>(GetOwningPlayer(), itemButtonClass);
		if (button != nullptr) {
			button->bIsFocusable = true;
			button->InitButton(iter);
			VerticalBox_ShopList->AddChild(button);
		}
	}

	auto widgets = VerticalBox_ShopList->GetAllChildren();
	if(widgets.Num() != 0)
	{
		nowItemButton = Cast<UShopButtonWidget>(widgets[0]);

		if(widgets.Num() > 1)
		{
			nextItemButton = Cast<UShopButtonWidget>(widgets[1]);
			preItemButton = Cast<UShopButtonWidget>(widgets[widgets.Num() - 1]);
		}

		nowItemButton->OnHoveredEvent();
	}
	SetItemInfo(nowItemButton->GetItem());
}

FString UShopMainWidget::GetAddOptionDescription_Material(EAddOptionsType_Material option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	case EAddOptionsType_Material::GIVE_ATC_DOWN:
		str = TEXT("무력의 저주");
		return str;
	case EAddOptionsType_Material::GIVE_BURN:
		str = TEXT("광열의 열기");
		return str;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		str = TEXT("강력한 파괴력");
		return str;
	case EAddOptionsType_Material::GIVE_DEF_DOWN:
		str = TEXT("방어의 저주");
		return str;
	case EAddOptionsType_Material::GIVE_FROZEN:
		str = TEXT("빙괴의 반향");
		return str;
	case EAddOptionsType_Material::GIVE_SHOCK:
		str = TEXT("봉뢰의 마찰");
		return str;
	case EAddOptionsType_Material::GIVE_SLOW:
		str = TEXT("속도의 저주");
		return str;
	case EAddOptionsType_Material::RECOVERY_HP:
		str = TEXT("강력한 회복력");
		return str;
	}return str;
}

void UShopMainWidget::SetItemInfo(AItemActor* value)
{
	if (value != nullptr) {
		FString str = "";
		str = TEXT("체력 : ") + FString::SanitizeFloat(value->GetItemStat().HP) + "\n" +
			TEXT("공격력 : ") + FString::SanitizeFloat(value->GetItemStat().ATC) + "\n" +
			TEXT("방어력 : ") + FString::SanitizeFloat(value->GetItemStat().DEF) + "\n" +
			TEXT("민첩성 : ") + FString::SanitizeFloat(value->GetItemStat().DEX);

		TextBlock_ItemStat->SetText(FText::FromString(str));

		TextBlock_Description->SetText(FText::FromString(value->GetItemInfo<FIteminfo>()->item_Description));

		TextBlock_ItemName->SetText(FText::FromName(value->GetItemInfo<FIteminfo>()->item_Name));

		str = "";
		if (Cast<AMaterialBaseActor>(value)->GetAddOption().Num() != 0) {
			for (auto iter : Cast<AMaterialBaseActor>(value)->GetAddOption())
			{
				str += GetAddOptionDescription_Material(iter) + "\n";
			}

			TextBlock_AddOption->SetText(FText::FromString(str));
		}

		Item_Image->SetBrushFromTexture(value->GetItemInfo<FIteminfo>()->item_Image);
	}
}

FReply UShopMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder) || InKeyEvent.GetKey() == FKey(EKeys::E))
	{
		NextItemButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder) || InKeyEvent.GetKey() == FKey(EKeys::Q))
	{
		PreItemButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		nowItemButton->OnPressedEvent();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right) || InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffShop();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}

void UShopMainWidget::NextItemButton()
{
	if(VerticalBox_ShopList->GetAllChildren().Num() > 1)
	{
		nowItemButton->OnUnhoveredEvent();

		preItemButton = nowItemButton;
		nowItemButton = nextItemButton;

		int32 index = VerticalBox_ShopList->GetAllChildren().Find(nowItemButton);
		if (index != VerticalBox_ShopList->GetAllChildren().Find(VerticalBox_ShopList->GetAllChildren().Last()))
		{
			nextItemButton = Cast<UShopButtonWidget>(VerticalBox_ShopList->GetAllChildren()[index + 1]);
		}
		else
		{
			nextItemButton = Cast<UShopButtonWidget>(VerticalBox_ShopList->GetAllChildren()[0]);
		}

		nowItemButton->OnHoveredEvent();
		nowItemButton->SetFocus();
		SetItemInfo(nowItemButton->GetItem());
	}
}

void UShopMainWidget::PreItemButton()
{
	if (VerticalBox_ShopList->GetAllChildren().Num() > 1)
	{
		nowItemButton->OnUnhoveredEvent();

		nextItemButton = nowItemButton;
		nowItemButton = preItemButton;

		int32 index = VerticalBox_ShopList->GetAllChildren().Find(nowItemButton);
		if (index != 0)
		{
			preItemButton = Cast<UShopButtonWidget>(VerticalBox_ShopList->GetAllChildren()[index - 1]);
		}
		else
		{
			preItemButton = Cast<UShopButtonWidget>(VerticalBox_ShopList->GetAllChildren().Last());
		}

		nowItemButton->OnHoveredEvent();
		nowItemButton->SetFocus();
		SetItemInfo(nowItemButton->GetItem());
	}
}
