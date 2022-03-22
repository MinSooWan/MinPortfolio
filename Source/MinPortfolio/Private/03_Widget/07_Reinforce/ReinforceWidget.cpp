// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/07_Reinforce/ReinforceButtonWidget.h"
#include "03_Widget/07_Reinforce/ReinforceInfoWidget.h"
#include "03_Widget/07_Reinforce/ReinforcePanelWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UReinforceWidget::ShowEquipmentEvent()
{
	UMG_ReinforcePanel->ShowEquipment();
	TextBlock_ItemType->SetText(FText::FromString(TEXT("강화할 장비를 선택하세요")));
	if (UMG_ReinforcePanel->GetButtons().Num() != 0) {
		nowItemButton = UMG_ReinforcePanel->GetButtons()[0];
		previousItemButton = UMG_ReinforcePanel->GetButtons().Last();
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_ReinforcePanel->GetButtons().Num() >= 2) {
			nextItemButton = UMG_ReinforcePanel->GetButtons()[1];
		}
		else
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons().Last();
		}

		SetItemInfo(nowItemButton->GetItem());
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString(""));
		TextBlock_ItemStat->SetText(FText::FromString(""));
		TextBlock_Description->SetText(FText::FromString(""));
		TextBlock_AddOption->SetText(FText::FromString(""));
		Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
	}

	SetFocus();
}

void UReinforceWidget::ShowMaterialEvent()
{
	UMG_ReinforcePanel->ShowMaterial();
	TextBlock_ItemType->SetText(FText::FromString(TEXT("강화재료를 선택하세요")));
	if (UMG_ReinforcePanel->GetButtons().Num() != 0) {
		nowItemButton = UMG_ReinforcePanel->GetButtons()[0];
		previousItemButton = UMG_ReinforcePanel->GetButtons().Last();
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_ReinforcePanel->GetButtons().Num() >= 2) {
			nextItemButton = UMG_ReinforcePanel->GetButtons()[1];
		}
		else
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons().Last();
		}

		SetItemInfo(nowItemButton->GetItem());
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString(""));
		TextBlock_ItemStat->SetText(FText::FromString(""));
		TextBlock_Description->SetText(FText::FromString(""));
		TextBlock_AddOption->SetText(FText::FromString(""));
		Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
	}

	SetFocus();
}

void UReinforceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundBlur_Image->SetVisibility(ESlateVisibility::Hidden);
	UMG_ReinforceInfo->SetVisibility(ESlateVisibility::Hidden);
}

FReply UReinforceWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Right") || InKeyEvent.GetKey() == FKey(EKeys::D))
	{
		PressedNextButton_Item();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Left") || InKeyEvent.GetKey() == FKey(EKeys::A))
	{
		PressedPreviousButton_Item();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Up") || InKeyEvent.GetKey() == FKey(EKeys::W))
	{
		PressedUpButton_Item();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Down") || InKeyEvent.GetKey() == FKey(EKeys::S))
	{
		PressedDownButton_Item();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		if (nowItemButton != nullptr) {
			if (bEquipment == true)
			{
				if (UMG_ReinforcePanel->GetButtons().Num() != 0) {
					material = nowItemButton->GetItem();
					UMG_ReinforceInfo->SetVisibility(ESlateVisibility::Visible);
					UMG_ReinforceInfo->SetInfo(equipment, material);
					GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
					GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Visible);
					UMG_ReinforceInfo->SetFocus();
				}
			}
			else if(bEquipment == false)
			{
				if (UMG_ReinforcePanel->GetButtons().Num() != 0) {
					equipment = nowItemButton->GetItem();
					ShowMaterialEvent();
					bEquipment = true;
				}
			}
		}
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right) || InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		if (nowItemButton != nullptr) {
			if (bEquipment == true)
			{
				material = nullptr;
				ShowEquipmentEvent();
				bEquipment = false;
			}
			else if (bEquipment == false)
			{
				SetVisibility(ESlateVisibility::Hidden);
				GetOwningPlayer<ACustomController>()->GetMainWidget()->OffReinforce();
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
				GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Hidden);
				GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
				UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
			}
		}
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}

void UReinforceWidget::SetItemInfo(AItemActor* item)
{
	TextBlock_ItemName->SetText(FText::FromName(item->GetItemInfo<FIteminfo>()->item_Name));
	Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 1)));

	Item_Image->SetBrushFromTexture(item->GetItemInfo<FIteminfo>()->item_Image);

	FString str = "";
	switch (item->GetItemInfo<FIteminfo>()->item_Type)
	{
	case EItemType::EQUIPMENT:
		if (item->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON) {
			str = TEXT("체력 : ") + FString::FromInt(item->GetItemStat().HP) + "\n" +
				TEXT("공격력 : ") + FString::FromInt(item->GetItemStat().ATC) + "\n" +
				TEXT("민첩성 : ") + FString::FromInt(item->GetItemStat().DEX);
		}
		else {
			str = TEXT("체력 : ") + FString::FromInt(item->GetItemStat().HP) + "\n" +
				TEXT("방어력 : ") + FString::FromInt(item->GetItemStat().DEF) + "\n" +
				TEXT("민첩성 : ") + FString::FromInt(item->GetItemStat().DEX);
		}
		break;
	case EItemType::MATERIAL:

		str = TEXT("체력 : ") + FString::SanitizeFloat(item->GetItemStat().HP) + "\n" +
			TEXT("공격력 : ") + FString::SanitizeFloat(item->GetItemStat().ATC) + "\n" +
			TEXT("방어력 : ") + FString::SanitizeFloat(item->GetItemStat().DEF) + "\n" +
			TEXT("민첩성 : ") + FString::SanitizeFloat(item->GetItemStat().DEX);


		break;
	}
	TextBlock_ItemStat->SetText(FText::FromString(str));

	TextBlock_Description->SetText(FText::FromString(item->GetItemInfo<FIteminfo>()->item_Description));

	str = "";
	switch (item->GetItemInfo<FIteminfo>()->item_Type)
	{
	case EItemType::EQUIPMENT:
		if (item->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::ARMOR) {
			if (Cast<AEquipmentActor>(item)->GetAddOption().Num() != 0) {
				for (auto iter : Cast<AEquipmentActor>(item)->GetAddOption())
				{
					str += GetAddOptionDescription_Equipment(iter) + "\n";
				}
			}
		}
		else
		{
			if (Cast<AWeaponBaseActor>(item)->GetAddOption().Num() != 0) {
				for (auto iter : Cast<AWeaponBaseActor>(item)->GetAddOption())
				{
					str += GetAddOptionDescription_WeaponItem(iter) + "\n";
				}
			}
		}
		break;
	case EItemType::MATERIAL:
		//FItemMaterial
		if (Cast<AMaterialBaseActor>(item)->GetAddOption().Num() != 0) {
			for (auto iter : Cast<AMaterialBaseActor>(item)->GetAddOption())
			{
				str += GetAddOptionDescription_Material(iter) + "\n";
			}
		}

		break;
	}
	TextBlock_AddOption->SetText(FText::FromString(str));
}

FString UReinforceWidget::GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Equipment::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	case EAddOptionsType_Equipment::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Equipment::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Equipment::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Equipment::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;
	case EAddOptionsType_Equipment::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	}return str;
}

FString UReinforceWidget::GetAddOptionDescription_Material(EAddOptionsType_Material option)
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
	case EAddOptionsType_Material::ADD_ATC_TIME:
		str = TEXT("익스클루시브 스펠");
		return str;
	case EAddOptionsType_Material::ADD_DEF_TIME:
		str = TEXT("강력한 회복력");
		return str;
	case EAddOptionsType_Material::ADD_DEX_TIME:
		str = TEXT("아이언 바디");
		return str;
	case EAddOptionsType_Material::ADD_HP_TIME:
		str = TEXT("리스토네이션");
		return str;
	}return str;
}

FString UReinforceWidget::GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Equipment_Weapon::GIVE_BURN:
		str = TEXT("광열의 열기");
		return str;
	case EAddOptionsType_Equipment_Weapon::GIVE_FROZEN:
		str = TEXT("빙괴의 반향");
		return str;
	case EAddOptionsType_Equipment_Weapon::GIVE_SHOCK:
		str = TEXT("봉뢰의 마찰");
		return str;
	case EAddOptionsType_Equipment_Weapon::GIVE_DAMAGE:
		str = TEXT("강력한 파괴력");
		return str;
	case EAddOptionsType_Equipment_Weapon::GIVE_SLOW:
		str = TEXT("속도의 저주");
		return str;
	case EAddOptionsType_Equipment_Weapon::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Equipment_Weapon::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Equipment_Weapon::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Equipment_Weapon::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	case EAddOptionsType_Equipment_Weapon::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;;
	case EAddOptionsType_Equipment_Weapon::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	}
	return str;
}

void UReinforceWidget::PressedNextButton_Item()
{
	if (UMG_ReinforcePanel->GetButtons().Num() >= 1) {
		if (nowItemButton->GetItem()->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
		{
			if (Cast<AEquipmentActor>(nowItemButton->GetItem())->GetEquipped() == true)
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
			}
			else
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
			}
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}
		previousItemButton = nowItemButton;
		nowItemButton = nextItemButton;

		int32 index = UMG_ReinforcePanel->GetButtons().Find(nowItemButton);
		if (index != UMG_ReinforcePanel->GetButtons().Find(GetInvnetoryPanel()->GetButtons().Last()))
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->GetItem());
	}
}

void UReinforceWidget::PressedPreviousButton_Item()
{
	if (UMG_ReinforcePanel->GetButtons().Num() >= 1) {
		if (nowItemButton->GetItem()->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
		{
			if (Cast<AEquipmentActor>(nowItemButton->GetItem())->GetEquipped() == true)
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
			}
			else
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
			}
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}
		nextItemButton = nowItemButton;
		nowItemButton = previousItemButton;

		int32 index = UMG_ReinforcePanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons().Last();
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->GetItem());
	}
}

void UReinforceWidget::PressedUpButton_Item()
{
	if (UMG_ReinforcePanel->GetButtons().Num() >= 7) {
		if (nowItemButton->GetItem()->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
		{
			if (Cast<AEquipmentActor>(nowItemButton->GetItem())->GetEquipped() == true)
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
			}
			else
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
			}
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}

		//현재 아이템 버튼을 설정
		if (UMG_ReinforcePanel->GetButtons().Find(nowItemButton) >= 6)
		{
			auto tempButton = UMG_ReinforcePanel->GetButtons()[UMG_ReinforcePanel->GetButtons().Find(nowItemButton) - 6];
			nowItemButton = tempButton;
		}
		else
		{
			int32 index = (UMG_ReinforcePanel->GetButtons().Find(UMG_ReinforcePanel->GetButtons().Last()) / 6) * 6 + UMG_ReinforcePanel->GetButtons().Find(nowItemButton);

			if (index > UMG_ReinforcePanel->GetButtons().Find(UMG_ReinforcePanel->GetButtons().Last()))
			{
				nowItemButton = UMG_ReinforcePanel->GetButtons().Last();
			}
			else
			{
				nowItemButton = UMG_ReinforcePanel->GetButtons()[index];
			}
		}

		//이전 아이템 버튼을 설정
		int32 index = UMG_ReinforcePanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons()[UMG_ReinforcePanel->GetButtons().Find(UMG_ReinforcePanel->GetButtons().Last())];
		}

		//다음 아이템 버튼을 설정
		if (index != UMG_ReinforcePanel->GetButtons().Find(UMG_ReinforcePanel->GetButtons().Last()))
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->GetItem());
	}
}

void UReinforceWidget::PressedDownButton_Item()
{
	if (UMG_ReinforcePanel->GetButtons().Num() >= 7) {
		if (nowItemButton->GetItem()->GetItemInfo<FIteminfo>()->item_Type == EItemType::EQUIPMENT)
		{
			if (Cast<AEquipmentActor>(nowItemButton->GetItem())->GetEquipped() == true)
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetEquippedImage());
			}
			else
			{
				nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
			}
		}
		else {
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		}

		int32 index = UMG_ReinforcePanel->GetButtons().Find(nowItemButton);
		int32 lastIndex = UMG_ReinforcePanel->GetButtons().Find(UMG_ReinforcePanel->GetButtons().Last());
		//현재 아이템 버튼을 설정
		if (index < lastIndex - (lastIndex % 6))
		{
			if (index + 6 <= lastIndex)
			{
				nowItemButton = UMG_ReinforcePanel->GetButtons()[index + 6];
			}
			else
			{
				nowItemButton = UMG_ReinforcePanel->GetButtons().Last();
			}
		}
		else
		{
			nowItemButton = UMG_ReinforcePanel->GetButtons()[index - (lastIndex / 6) * 6];
		}

		//이전 아이템 버튼을 설정
		index = UMG_ReinforcePanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_ReinforcePanel->GetButtons()[lastIndex];
		}

		//다음 아이템 버튼을 설정
		if (index != lastIndex)
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_ReinforcePanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->GetItem());
	}
}

void UReinforceWidget::OnReinforceWidget()
{
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnReinforce();
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Visible);
	ShowEquipmentEvent();
}
