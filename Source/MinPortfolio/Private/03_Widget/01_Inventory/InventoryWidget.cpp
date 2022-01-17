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

	SetVisibility(ESlateVisibility::Visible);
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

void UInventoryWidget::SetItemInfo(FIteminfo* info)
{
	
	TextBlock_ItemName->SetText(FText::FromName(info->item_Name));

	FString str = "";
	switch (info->item_Type)
	{
	case EItemType::EQUIPMENT:
		if (((FEquipment*)(info))->equipment_Type == EEquipmentType::WEAPON) {
			str = "체력 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.HP) + "\n" +
				"공격력 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.ATC) + "\n" +
				"민첩성 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEX);
		}
		else {
			str = "체력 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.HP) + "\n" +
				"방어력 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEF) + "\n" +
				"민첩성 : " + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEX);
		}
		break;
	case EItemType::MATERIAL:

		str = "체력 : " + FString::FromInt(((FItemMaterial*)(info))->materialStat.HP) + "\n" +
			"공격력 : " + FString::FromInt(((FItemMaterial*)(info))->materialStat.ATC) + "\n" +
			"방어력 : " + FString::FromInt(((FItemMaterial*)(info))->materialStat.DEF) + "\n" +
			"민첩성 : " + FString::FromInt(((FItemMaterial*)(info))->materialStat.DEX);
		break;
	}
	TextBlock_ItemStat->SetText(FText::FromString(str));

	TextBlock_Description->SetText(FText::FromString(info->item_Description));

	str = "";
	switch (info->item_Type)
	{
	case EItemType::EQUIPMENT:
		
		for(auto iter : ((FEquipment*)(info))->addOption)
		{
			str += GetAddOptionDescription_Equipment(iter) + "\n";
		}
		break;

	case EItemType::BATTLE_ITEM:
		if (((FBattleItem*)(info))->battleItemType == EBattleItemType::BATTLE_CONSUME) {
			for (auto iter : ((FBattle_Consume*)(info))->addOption)
			{
				str += GetAddOptionDescription_BattleItem(iter) + "\n";
			}
		}
		else
		{
			for (auto iter : ((FRecovery_Consume*)(info))->addOption)
			{
				str += GetAddOptionDescription_RecoveryItem(iter) + "\n";
			}
		}
		break;

	case EItemType::MATERIAL:

		for (auto iter : ((FItemMaterial*)(info))->addOption)
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
		str = "공격력 강화";
		return str;
	case EAddOptionsType_Equipment::ADD_DEX:
		str = "민첩성 강화";
		return str;
	case EAddOptionsType_Equipment::ADD_HP:
		str = "체력 강화";
		return str;
	case EAddOptionsType_Equipment::ADD_DEF:
		str = "방어력 강화";
		return str;
	case EAddOptionsType_Equipment::ADD_EXP:
		str = "빠른 성장";
		return str;
	case EAddOptionsType_Equipment::ADD_ITEM:
		str = "더 많이!";
		return str;
	}return str;
}

FString UInventoryWidget::GetAddOptionDescription_Material(EAddOptionsType_Material option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		str = "공격력 강화";
		return str;
	case EAddOptionsType_Material::ADD_DEF:
		str = "방어력 강화";
		return str;
	case EAddOptionsType_Material::ADD_DEX:
		str = "민첩성 강화";
		return str;
	case EAddOptionsType_Material::ADD_EXP:
		str = "빠른 성장";
		return str;
	case EAddOptionsType_Material::ADD_HP:
		str = "체력 강화";
		return str;
	case EAddOptionsType_Material::ADD_ITEM:
		str = "더 많이!";
		return str;
	case EAddOptionsType_Material::GIVE_ATC_DOWN:
		str = "무력의 저주";
		return str;
	case EAddOptionsType_Material::GIVE_BURN:
		str = "광열의 연기";
		return str;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		str = "강력한 파괴력";
		return str;
	case EAddOptionsType_Material::GIVE_DEF_DOWN:
		str = "방어의 저주";
		return str;
	case EAddOptionsType_Material::GIVE_FROZEN:
		str = "빙괴의 반향";
		return str;
	case EAddOptionsType_Material::GIVE_SHOCK:
		str = "봉뢰의 마찰";
		return str;
	case EAddOptionsType_Material::GIVE_SLOW:
		str = "속도의 저주";
		return str;
	case EAddOptionsType_Material::RECOVERY_HP:
		str = "강력한 회복력";
		return str;
	}return str;
}

FString UInventoryWidget::GetAddOptionDescription_BattleItem(EAddOptionsType_BattleItem option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_BattleItem::GIVE_ATC_DOWN:
		str = "무력의 저주";
		return str;
	case EAddOptionsType_BattleItem::GIVE_BURN:
		str = "광열의 연기";
		return str;
	case EAddOptionsType_BattleItem::GIVE_DAMAGE:
		str = "강력한 파괴력";
		return str;
	case EAddOptionsType_BattleItem::GIVE_DEF_DOWN:
		str = "방어의 저주";
		return str;
	case EAddOptionsType_BattleItem::GIVE_FROZEN:
		str = "빙괴의 반향";
		return str;
	case EAddOptionsType_BattleItem::GIVE_SHOCK:
		str = "봉뢰의 마찰";
		return str;
	case EAddOptionsType_BattleItem::GIVE_SLOW:
		str = "속도의 저주";
		return str;
	}return str;
}

FString UInventoryWidget::GetAddOptionDescription_RecoveryItem(EAddOptionsType_RecoveryItem option)
{
	FString str;
	switch (option)
	{
	case EAddOptionsType_RecoveryItem::ADD_ATC_TIME:
		str = "힘의 축복";
		return str;
	case EAddOptionsType_RecoveryItem::RECOVERY_HP:
		str = "강력한 회복력";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_DEF_TIME:
		str = "수호의 축복";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_DEX_TIME:
		str = "질풍의 축복";
		return str;
	case EAddOptionsType_RecoveryItem::ADD_HP_TIME:
		str = "생명의 축복";
		return str;
	}
	return str;
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
			nowTypeButton->OnClicked.Broadcast();
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
			nowTypeButton->OnClicked.Broadcast();
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
