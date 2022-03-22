// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceInfoWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/07_Reinforce/ReinforceCheckWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "03_Widget/07_Reinforce/ReinforceeAddOptionWidget.h"
#include "03_Widget/07_Reinforce/ReinforceWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBox.h"
#include "Kismet/KismetInputLibrary.h"

void UReinforceInfoWidget::SetInfo(AItemActor* equipment, AItemActor* material)
{
	VerticalBox_Reinforce->ClearChildren();
	if (equipment != nullptr) {
		equipmentItem = equipment;

		FString str = "";
		str = TEXT("체력 : ") + FString::FromInt(equipment->GetItemStat().HP) + "\n" +
			TEXT("공격력 : ") + FString::FromInt(equipment->GetItemStat().ATC) + "\n" +
			TEXT("방어력 : ") + FString::FromInt(equipment->GetItemStat().DEF) + "\n" +
			TEXT("민첩성 : ") + FString::FromInt(equipment->GetItemStat().DEX);
		TextBlock_EquipmentStat->SetText(FText::FromString(str));

		str = "";
		if (equipment->IsA<AArmorBaseActor>()) {
			for (auto iter : Cast<AEquipmentActor>(equipment)->GetAddOption())
			{
				str += GetAddOptionDescription_Equipment(iter) + "\n";
			}
		}
		else if(equipment->IsA<AWeaponBaseActor>())
		{
			for (auto iter : Cast<AWeaponBaseActor>(equipment)->GetAddOption())
			{
				str += GetAddOptionDescription_WeaponItem(iter) + "\n";
			}
		}
		TextBlock_EquipmentAddOption->SetText(FText::FromString(str));

		Image_Equipment->SetBrushFromSoftTexture(equipment->GetItemInfo<FIteminfo>()->item_Image);
	}

	if(material != nullptr)
	{
		materialItem = material;
		FString str = "";
		str = TEXT("체력 : ") + FString::FromInt(material->GetItemStat().HP) + "\n" +
			TEXT("공격력 : ") + FString::FromInt(material->GetItemStat().ATC) + "\n" +
			TEXT("방어력 : ") + FString::FromInt(material->GetItemStat().DEF) + "\n" +
			TEXT("민첩성 : ") + FString::FromInt(material->GetItemStat().DEX);
		TextBlock_Materia->SetText(FText::FromString(str));

		str = "";
		if (material->IsA<AMaterialBaseActor>()) {
			for (auto iter : Cast<AMaterialBaseActor>(material)->GetAddOption())
			{
				str += GetAddOptionDescription_Material(iter) + "\n";
			}
		}
		TextBlock_MaterialAddOption->SetText(FText::FromString(str));

		Image_Material->SetBrushFromSoftTexture(material->GetItemInfo<FIteminfo>()->item_Image);
	}

	if(equipment != nullptr && material != nullptr)
	{
		FString str = "";
		str = TEXT("체력 : ") + FString::FromInt(material->GetItemStat().HP + equipment->GetItemStat().HP) + "\n" +
			TEXT("공격력 : ") + FString::FromInt(material->GetItemStat().ATC + equipment->GetItemStat().ATC) + "\n" +
			TEXT("방어력 : ") + FString::FromInt(material->GetItemStat().DEF + equipment->GetItemStat().DEF) + "\n" +
			TEXT("민첩성 : ") + FString::FromInt(material->GetItemStat().DEX + equipment->GetItemStat().DEX);
		TextBlock_ReinforceStat->SetText(FText::FromString(str));

		Image_Reinforce->SetBrushFromTexture(equipment->GetItemInfo<FIteminfo>()->item_Image);

		if(equipment->IsA<AWeaponBaseActor>())
		{
			for(auto iter : Cast<AWeaponBaseActor>(equipment)->GetAddOption())
			{
				auto button = CreateWidget<UReinforceeAddOptionWidget>(GetOwningPlayer(), addOptionButtonClass);
				button->SetAddOptionText(GetAddOptionDescription_WeaponItem(iter));
				button->SetAddOption_Weapon(iter);
				button->SetIsWeapon(true);
				VerticalBox_Reinforce->AddChild(button);
			}

			for (auto iter : Cast<AMaterialBaseActor>(material)->GetAddOption())
			{
				if (!GetAddOptionDescription_ReinforceToWeapon(iter).Equals("")) {
					auto button = CreateWidget<UReinforceeAddOptionWidget>(GetOwningPlayer(), addOptionButtonClass);
					button->GetTextBlock_AddOption()->SetText(FText::FromString(GetAddOptionDescription_ReinforceToWeapon(iter)));
					button->SetAddOption_Weapon(GetAddOptionToWeapon(iter));
					button->SetIsWeapon(true);
					VerticalBox_Reinforce->AddChild(button);
				}
			}
		}
		else if(equipment->IsA<AArmorBaseActor>())
		{
			for (auto iter : Cast<AEquipmentActor>(equipment)->GetAddOption())
			{
				auto button = CreateWidget<UReinforceeAddOptionWidget>(GetOwningPlayer(), addOptionButtonClass);
				str += GetAddOptionDescription_Equipment(iter);
				button->SetAddOption_Armor(iter);
				VerticalBox_Reinforce->AddChild(button);
			}

			for (auto iter : Cast<AMaterialBaseActor>(material)->GetAddOption())
			{
				if (!GetAddOptionDescription_ReinforceToArmor(iter).Equals("")) {
					auto button = CreateWidget<UReinforceeAddOptionWidget>(GetOwningPlayer(), addOptionButtonClass);
					button->SetAddOptionText(GetAddOptionDescription_ReinforceToArmor(iter));
					button->SetAddOption_Armor(GetAddOptionToArmor(iter));
					VerticalBox_Reinforce->AddChild(button);
				}
			}
		}

		if(VerticalBox_Reinforce->GetAllChildren().Num() > 0)
		{
			nowAddOptionButton = Cast<UReinforceeAddOptionWidget>(VerticalBox_Reinforce->GetAllChildren()[0]);
			nowAddOptionButton->SetHoveredImage();
		}
	}
}

FString UReinforceInfoWidget::GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option)
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

FString UReinforceInfoWidget::GetAddOptionDescription_Material(EAddOptionsType_Material option)
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

FString UReinforceInfoWidget::GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option)
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

FString UReinforceInfoWidget::GetAddOptionDescription_ReinforceToArmor(EAddOptionsType_Material option)
{
	FString str = "";
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	}return str;
}

FString UReinforceInfoWidget::GetAddOptionDescription_ReinforceToWeapon(EAddOptionsType_Material option)
{
	FString str = "";
	switch (option)
	{
	case EAddOptionsType_Material::GIVE_BURN:
		str = TEXT("광열의 열기");
		return str;
	case EAddOptionsType_Material::GIVE_FROZEN:
		str = TEXT("빙괴의 반향");
		return str;
	case EAddOptionsType_Material::GIVE_SHOCK:
		str = TEXT("봉뢰의 마찰");
		return str;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		str = TEXT("강력한 파괴력");
		return str;
	case EAddOptionsType_Material::GIVE_SLOW:
		str = TEXT("속도의 저주");
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = TEXT("방어력 강화");
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = TEXT("민첩성 강화");
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = TEXT("체력 강화");
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = TEXT("더 많이!");
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = TEXT("빠른 성장");
		return str;;
	case EAddOptionsType_Material::ADD_ATC:
		str = TEXT("공격력 강화");
		return str;
	}
	return str;
}

EAddOptionsType_Equipment UReinforceInfoWidget::GetAddOptionToArmor(EAddOptionsType_Material option)
{
	FString str = "";
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		return EAddOptionsType_Equipment::ADD_ATC;
	case EAddOptionsType_Material::ADD_DEX:
		return EAddOptionsType_Equipment::ADD_DEX;
	case EAddOptionsType_Material::ADD_HP:
		return EAddOptionsType_Equipment::ADD_HP;
	case EAddOptionsType_Material::ADD_DEF:
		return EAddOptionsType_Equipment::ADD_DEF;
	case EAddOptionsType_Material::ADD_EXP:
		return EAddOptionsType_Equipment::ADD_EXP;
	case EAddOptionsType_Material::ADD_ITEM:
		return EAddOptionsType_Equipment::ADD_ITEM;
	}return EAddOptionsType_Equipment::ADD_MAX;
}

EAddOptionsType_Equipment_Weapon UReinforceInfoWidget::GetAddOptionToWeapon(EAddOptionsType_Material option)
{
	switch (option)
	{
	case EAddOptionsType_Material::GIVE_BURN:
		return EAddOptionsType_Equipment_Weapon::GIVE_BURN;
	case EAddOptionsType_Material::GIVE_FROZEN:
		return EAddOptionsType_Equipment_Weapon::GIVE_FROZEN;
	case EAddOptionsType_Material::GIVE_SHOCK:
		return EAddOptionsType_Equipment_Weapon::GIVE_SHOCK;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		return EAddOptionsType_Equipment_Weapon::GIVE_DAMAGE;
	case EAddOptionsType_Material::GIVE_SLOW:
		return EAddOptionsType_Equipment_Weapon::GIVE_SLOW;
	case EAddOptionsType_Material::ADD_DEF:
		return EAddOptionsType_Equipment_Weapon::ADD_DEF;
	case EAddOptionsType_Material::ADD_DEX:
		return EAddOptionsType_Equipment_Weapon::ADD_DEX;
	case EAddOptionsType_Material::ADD_HP:
		return EAddOptionsType_Equipment_Weapon::ADD_HP;
	case EAddOptionsType_Material::ADD_ITEM:
		return EAddOptionsType_Equipment_Weapon::ADD_ITEM;
	case EAddOptionsType_Material::ADD_EXP:
		return EAddOptionsType_Equipment_Weapon::ADD_EXP;
	case EAddOptionsType_Material::ADD_ATC:
		return EAddOptionsType_Equipment_Weapon::ADD_ATC;
	}
	return EAddOptionsType_Equipment_Weapon::ADD_MAX;
}

FReply UReinforceInfoWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down) || InKeyEvent.GetKey() == FKey(EKeys::D))
	{
		PressedDownEvent();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up) || InKeyEvent.GetKey() == FKey(EKeys::A))
	{
		PressedUpEvent();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		if (useAddOptions_Armor.Num() < 3 || useAddOptions_Weapon.Num() < 3) {
			if (VerticalBox_Reinforce->GetAllChildren().Num() > 0) {
				if (nowAddOptionButton->GetSelect() == false) {
					if (nowAddOptionButton->GetIsWeapon() == true)
					{
						useAddOptions_Weapon.Add(nowAddOptionButton->GetAddOption_Weapon());
					}
					else
					{
						useAddOptions_Armor.Add(nowAddOptionButton->GetAddOption_Armor());
					}

					nowAddOptionButton->SetSelect(true);
				}
				else
				{
					if (nowAddOptionButton->GetIsWeapon() == true)
					{
						useAddOptions_Weapon.Remove(nowAddOptionButton->GetAddOption_Weapon());
					}
					else
					{
						useAddOptions_Armor.Remove(nowAddOptionButton->GetAddOption_Armor());
					}

					nowAddOptionButton->SetSelect(false);
				}
			}
		}
		else
		{
			if (nowAddOptionButton->GetSelect() == false) {
				CanvasPanel_addOptionMany->SetVisibility(ESlateVisibility::Hidden);
				Button_Check->SetFocus();
			}
			else
			{
				if (nowAddOptionButton->GetIsWeapon() == true)
				{
					useAddOptions_Weapon.Remove(nowAddOptionButton->GetAddOption_Weapon());
				}
				else
				{
					useAddOptions_Armor.Remove(nowAddOptionButton->GetAddOption_Armor());
				}

				nowAddOptionButton->SetSelect(false);
			}
		}
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_Special_Right) || InKeyEvent.GetKey() == FKey(EKeys::Tab))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceItemCheck()->InitCheckWidget(equipmentItem, materialItem);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceItemCheck()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceItemCheck()->SetFocus();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right) || InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_ReinforceWidget()->SetFocus();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}

void UReinforceInfoWidget::PressedDownEvent()
{
	if (VerticalBox_Reinforce->GetAllChildren().Num() > 1) {
		if (nowAddOptionButton->GetSelect() == true)
		{
			nowAddOptionButton->SetSelectImage();
		}
		else
		{
			nowAddOptionButton->SetDefaultImage();
		}

		if(VerticalBox_Reinforce->GetAllChildren().Last() == nowAddOptionButton)
		{
			nowAddOptionButton = Cast<UReinforceeAddOptionWidget>(VerticalBox_Reinforce->GetAllChildren()[0]);
		}
		else
		{
			nowAddOptionButton = Cast<UReinforceeAddOptionWidget>(VerticalBox_Reinforce->GetAllChildren()[VerticalBox_Reinforce->GetAllChildren().Find(nowAddOptionButton) + 1]);
		}

		nowAddOptionButton->SetHoveredImage();
	}
}

void UReinforceInfoWidget::PressedUpEvent()
{
	if (VerticalBox_Reinforce->GetAllChildren().Num() > 1) {
		if (nowAddOptionButton->GetSelect() == true)
		{
			nowAddOptionButton->SetSelectImage();
		}
		else
		{
			nowAddOptionButton->SetDefaultImage();
		}

		if (VerticalBox_Reinforce->GetAllChildren()[0] == nowAddOptionButton)
		{
			nowAddOptionButton = Cast<UReinforceeAddOptionWidget>(VerticalBox_Reinforce->GetAllChildren().Last());
		}
		else
		{
			nowAddOptionButton = Cast<UReinforceeAddOptionWidget>(VerticalBox_Reinforce->GetAllChildren()[VerticalBox_Reinforce->GetAllChildren().Find(nowAddOptionButton) - 1]);
		}

		nowAddOptionButton->SetHoveredImage();
	}
}

void UReinforceInfoWidget::PressedCheckButton()
{
	SetFocus();
	CanvasPanel_addOptionMany->SetVisibility(ESlateVisibility::Hidden);
}

void UReinforceInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Check->OnPressed.AddDynamic(this, &UReinforceInfoWidget::PressedCheckButton);
	CanvasPanel_addOptionMany->SetVisibility(ESlateVisibility::Hidden);
}
