// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryWidget.h"

#include <string>

#include "03_Widget/01_Inventory/InventoryPanelWidget.h"
#include "Components/Button.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_All->OnClicked.AddDynamic(this, &UInventoryWidget::ShowAllEvent);
	Button_Equipment->OnClicked.AddDynamic(this, &UInventoryWidget::ShowEquipmentEvent);
	Button_Material->OnClicked.AddDynamic(this, &UInventoryWidget::ShowMaterialEvent);
	Button_Tool->OnClicked.AddDynamic(this, &UInventoryWidget::ShowToolEvent);
	Button_BattleItem->OnClicked.AddDynamic(this, &UInventoryWidget::ShowBattleItemEvent);

	typeButtons.Emplace(Button_All);
	typeButtons.Emplace(Button_Equipment);
	typeButtons.Emplace(Button_Material);
	typeButtons.Emplace(Button_Tool);
	typeButtons.Emplace(Button_BattleItem);
}

void UInventoryWidget::ShowAllEvent()
{
	UMG_InvnetoryPanel->ShowAll(GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp());
}

void UInventoryWidget::ShowEquipmentEvent()
{
	UMG_InvnetoryPanel->ShowEquipment(GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp());
}

void UInventoryWidget::ShowMaterialEvent()
{
	UMG_InvnetoryPanel->ShowMaterial(GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp());
}

void UInventoryWidget::ShowToolEvent()
{
	UMG_InvnetoryPanel->ShowTool(GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp());
}

void UInventoryWidget::ShowBattleItemEvent()
{
	UMG_InvnetoryPanel->ShowBattleItem(GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp());
}

FReply UInventoryWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey("Gamepad_RightShoulder"))
	{
		PressedNextButton_Type();
		return FReply::Handled();
	}
	else if(InKeyEvent.GetKey() == FKey("Gamepad_LeftShoulder"))
	{
		PressedPreviousButton_Type();
		return FReply::Handled();
	}
	return FReply::Handled();
}

void UInventoryWidget::SetItemInfo(const FIteminfo& info)
{
	TextBlock_ItemName->SetText(FText::FromName(info.item_Name));

	FString str = "";
	switch (info.item_Type)
	{
	case EItemType::EQUIPMENT:
		if (Cast<FEquipment>(&info)->equipment_Type == EEquipmentType::WEAPON) {
			str = "ü�� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.HP) + "\n" +
				"���ݷ� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.ATC) + "\n" +
				"��ø�� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.DEX);
		}
		else {
			str = "ü�� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.HP) + "\n" +
				"���� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.DEF) + "\n" +
				"��ø�� : " + FString::FromInt(Cast<FEquipment>(&info)->equipmentStat.DEX);
		}
		break;
	case EItemType::MATERIAL:

		str = "ü�� : " + FString::FromInt(Cast<FItemMaterial>(&info)->materialStat.HP) + "\n" +
			"���ݷ� : " + FString::FromInt(Cast<FItemMaterial>(&info)->materialStat.ATC) + "\n" +
			"���� : " + FString::FromInt(Cast<FItemMaterial>(&info)->materialStat.DEF) + "\n" +
			"��ø�� : " + FString::FromInt(Cast<FItemMaterial>(&info)->materialStat.DEX);
		break;
	}
	TextBlock_ItemStat->SetText(FText::FromString(str));

	TextBlock_Description->SetText(FText::FromString(info.item_Description));

	str = "";
	switch (info.item_Type)
	{
	case EItemType::EQUIPMENT:
		
		for(auto iter : Cast<FEquipment>(&info)->addOption)
		{
			str += GetAddOptionDescription_Equipment(iter) + "\n";
		}
		break;

	case EItemType::BATTLE_ITEM:
		if (Cast<FBattleItem>(&info)->battleItemType == EBattleItemType::BATTLE_CONSUME) {
			for (auto iter : Cast<FBattle_Consume>(&info)->addOption)
			{
				str += GetAddOptionDescription_BattleItem(iter) + "\n";
			}
		}
		else
		{
			for (auto iter : Cast<FRecovery_Consume>(&info)->addOption)
			{
				str += GetAddOptionDescription_RecoveryItem(iter) + "\n";
			}
		}
		break;

	case EItemType::MATERIAL:

		for (auto iter : Cast<FItemMaterial>(&info)->addOption)
		{
			str += GetAddOptionDescription_Material(iter) + "\n";
		}
		break;
	}
	TextBlock_AddOption->SetText(FText::FromString(str));
}

FString UInventoryWidget::GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Equipment::ADD_ATC:
		str = "���ݷ� ��ȭ";
		return str;
	case EAddOptionsType_Equipment::ADD_DEX:
		str = "��ø�� ��ȭ";
		return str;
	case EAddOptionsType_Equipment::ADD_HP:
		str = "ü�� ��ȭ";
		return str;
	case EAddOptionsType_Equipment::ADD_DEF:
		str = "���� ��ȭ";
		return str;
	case EAddOptionsType_Equipment::ADD_EXP:
		str = "���� ����";
		return str;
	case EAddOptionsType_Equipment::ADD_ITEM:
		str = "�� ����!";
		return str;
	}
}

FString UInventoryWidget::GetAddOptionDescription_Material(EAddOptionsType_Material option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		str = "���ݷ� ��ȭ";
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = "���� ��ȭ";
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = "��ø�� ��ȭ";
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = "���� ����";
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = "ü�� ��ȭ";
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = "�� ����!";
		return str;
	case EAddOptionsType_Material::GIVE_ATC_DOWN:
		str = "������ ����";
		return str;
	case EAddOptionsType_Material::GIVE_BURN:
		str = "������ ����";
		return str;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		str = "������ �ı���";
		return str;
	case EAddOptionsType_Material::GIVE_DEF_DOWN:
		str = "����� ����";
		return str;
	case EAddOptionsType_Material::GIVE_FROZEN:
		str = "������ ����";
		return str;
	case EAddOptionsType_Material::GIVE_SHOCK:
		str = "������ ����";
		return str;
	case EAddOptionsType_Material::GIVE_SLOW:
		str = "�ӵ��� ����";
		return str;
	case EAddOptionsType_Material::RECOVERY_HP:
		str = "������ ȸ����";
		return str;
	}
}

FString UInventoryWidget::GetAddOptionDescription_BattleItem(EAddOptionsType_BattleItem option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_BattleItem::GIVE_ATC_DOWN:
		str = "������ ����";
		return str;
	case EAddOptionsType_BattleItem::GIVE_BURN:
		str = "������ ����";
		return str;
	case EAddOptionsType_BattleItem::GIVE_DAMAGE:
		str = "������ �ı���";
		return str;
	case EAddOptionsType_BattleItem::GIVE_DEF_DOWN:
		str = "����� ����";
		return str;
	case EAddOptionsType_BattleItem::GIVE_FROZEN:
		str = "������ ����";
		return str;
	case EAddOptionsType_BattleItem::GIVE_SHOCK:
		str = "������ ����";
		return str;
	case EAddOptionsType_BattleItem::GIVE_SLOW:
		str = "�ӵ��� ����";
		return str;
	}
}

FString UInventoryWidget::GetAddOptionDescription_RecoveryItem(EAddOptionsType_RecoveryItem option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_RecoveryItem::ADD_ATC_TIME:
		str = "���� �ູ";
		return str;
	case EAddOptionsType_RecoveryItem::RECOVERY_HP:
		str = "������ ȸ����";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_DEF_TIME:
		str = "��ȣ�� �ູ";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_DEX_TIME:
		str = "��ǳ�� �ູ";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_HP_TIME:
		str = "������ �ູ";
		return str;
	}
}

void UInventoryWidget::PressedNextButton_Type()
{
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
	previousTypeButton = nowTypeButton;
	nowTypeButton = nextTypeButton;

	for (int i = 0; i < typeButtons.Num(); i++)
	{
		auto iter = typeButtons[i];

		if (iter == nowTypeButton)
		{
			if (i == typeButtons.Num() - 1)
			{
				nextTypeButton = typeButtons[0];
			}
			else
			{
				nextTypeButton = typeButtons[i + 1];
			}
			nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
			break;
		}
	}
}

void UInventoryWidget::PressedPreviousButton_Type()
{
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(defaultImage);
	nextTypeButton = nowTypeButton;
	nowTypeButton = previousTypeButton;

	for (int i = 0; i < typeButtons.Num(); i++)
	{
		auto iter = typeButtons[i];

		if (iter == nowTypeButton)
		{
			if (i == 0)
			{
				previousTypeButton = typeButtons[typeButtons.Num() - 1];
			}
			else
			{
				previousTypeButton = typeButtons[i - 1];
			}
			nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);
			break;
		}
	}
}

void UInventoryWidget::PressedNextButton_Item()
{
	nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
	previousItemButton = nowItemButton;
	nowItemButton = nextItemButton;

	for (int i = 0; i < UMG_InvnetoryPanel->GetButtons().Num(); i++)
	{
		auto iter = UMG_InvnetoryPanel->GetButtons()[i];

		if (iter == nowItemButton)
		{
			if (i == UMG_InvnetoryPanel->GetButtons().Num() - 1)
			{
				nextItemButton = UMG_InvnetoryPanel->GetButtons()[0];
			}
			else
			{
				nextItemButton = UMG_InvnetoryPanel->GetButtons()[i + 1];
			}
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
			nowItemButton->SetFocus();
			break;
		}
	}
}

void UInventoryWidget::PressedPreviousButton_Item()
{
	nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
	nextItemButton = nowItemButton;
	nowItemButton = previousItemButton;

	for (int i = 0; i < UMG_InvnetoryPanel->GetButtons().Num(); i++)
	{
		auto iter = UMG_InvnetoryPanel->GetButtons()[i];

		if (iter == nowItemButton)
		{
			if (i == 0)
			{
				previousItemButton = UMG_InvnetoryPanel->GetButtons()[UMG_InvnetoryPanel->GetButtons().Num() - 1];
			}
			else
			{
				previousItemButton = UMG_InvnetoryPanel->GetButtons()[i - 1];
			}
			nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
			nowItemButton->SetFocus();
			break;
		}
	}
}
