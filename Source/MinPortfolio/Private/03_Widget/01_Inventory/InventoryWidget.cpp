// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/InventoryWidget.h"
#include <string>
#include "03_Widget/01_Inventory/InventoryPanelWidget.h"
#include "Components/Button.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
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

	SetVisibility(ESlateVisibility::Hidden);
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

	if (InKeyEvent.GetKey() == FKey("Gamepad_RightShoulder"))
	{
		PressedNextButton_Type();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_LeftShoulder"))
	{
		PressedPreviousButton_Type();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Right"))
	{
		PressedNextButton_Item();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_DPad_Left"))
	{
		PressedPreviousButton_Item();
		return FReply::Handled();
	}
	else if(InKeyEvent.GetKey() == FKey("Gamepad_DPad_Up"))
	{
		PressedUpButton_Item();
	}
	else if(InKeyEvent.GetKey() == FKey("Gamepad_DPad_Down"))
	{
		PressedDownButton_Item();
	}
	
	return FReply::Handled();
}

FReply UInventoryWidget::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyUp(InGeometry, InKeyEvent);
	//EKeys::Daydream_Right_Trackpad_Y
	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		nowItemButton->GetButton_item()->OnReleased.Broadcast();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetMenuWidget()->SetFocus();
		SetVisibility(ESlateVisibility::Hidden);
	}
	return FReply::Handled();
}

void UInventoryWidget::SetItemInfo(FIteminfo* info)
{
	TextBlock_ItemName->SetText(FText::FromName(info->item_Name));
	Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 1)));
	Item_Type->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 1)));

	Item_Image->SetBrushFromTexture(info->item_Image);
	Item_Type->SetBrushFromTexture(SetItemTypeImage(info->item_Type));

	FString str = "";
	switch (info->item_Type)
	{
	case EItemType::EQUIPMENT:
		if (((FEquipment*)(info))->equipment_Type == EEquipmentType::WEAPON) {
			str = TEXT("체력 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.HP) + "\n" +
				TEXT("공격력 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.ATC) + "\n" +
				TEXT("민첩성 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEX);
		}
		else {
			str = TEXT("체력 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.HP) + "\n" +
				TEXT("방어력 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEF) + "\n" +
				TEXT("민첩성 : ") + FString::FromInt(((FEquipment*)(info))->equipmentStat.DEX);
		}
		break;
	case EItemType::MATERIAL:
	
		str = TEXT("체력 : ") + FString::SanitizeFloat(((FItemMaterial*)(info))->materialStat.HP) + "\n" +
			TEXT("공격력 : ") + FString::SanitizeFloat(((FItemMaterial*)(info))->materialStat.ATC) + "\n" +
			TEXT("방어력 : ") + FString::SanitizeFloat(((FItemMaterial*)(info))->materialStat.DEF) + "\n" +
			TEXT("민첩성 : ") + FString::SanitizeFloat(((FItemMaterial*)(info))->materialStat.DEX);
			
		
		break;
	}
	TextBlock_ItemStat->SetText(FText::FromString(str));

	TextBlock_Description->SetText(FText::FromString(info->item_Description));

	str = "";
	switch (info->item_Type)
	{
	case EItemType::EQUIPMENT:

		if (((FEquipment*)(info))->addOption.Num() != 0) {
			for (auto iter : ((FEquipment*)(info))->addOption)
			{
				str += GetAddOptionDescription_Equipment(iter) + "\n";
			}
		}
		break;

	case EItemType::BATTLE_ITEM:
		if (((FBattleItem*)(info))->battleItemType == EBattleItemType::BATTLE_CONSUME) {
			if (((FBattle_Consume*)(info))->addOption.Num() != 0) {
				for (auto iter : ((FBattle_Consume*)(info))->addOption)
				{
					str += GetAddOptionDescription_BattleItem(iter) + "\n";
				}
			}
		}
		else
		{
			if (((FRecovery_Consume*)(info))->addOption.Num() != 0) {
				for (auto iter : ((FRecovery_Consume*)(info))->addOption)
				{
					str += GetAddOptionDescription_RecoveryItem(iter) + "\n";
				}
			}
		}
		break;

	case EItemType::MATERIAL:
		
		if (((FItemMaterial*)(info))->addOption.Num() != 0) {
			for (auto iter : ((FItemMaterial*)(info))->addOption)
			{
				str += GetAddOptionDescription_Material(iter) + "\n";
			}
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

	if (UMG_InvnetoryPanel->GetButtons().Num() != 0) {
		nowItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		previousItemButton = UMG_InvnetoryPanel->GetButtons().Last();
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_InvnetoryPanel->GetButtons().Num() >= 2) {
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[1];
		}
		
		SetItemInfo(nowItemButton->item_info);
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString(""));
		TextBlock_ItemStat->SetText(FText::FromString(""));
		TextBlock_Description->SetText(FText::FromString(""));
		TextBlock_AddOption->SetText(FText::FromString(""));
		Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
		Item_Type->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
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

	if (UMG_InvnetoryPanel->GetButtons().Num() != 0) {
		nowItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		previousItemButton = UMG_InvnetoryPanel->GetButtons().Last();
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_InvnetoryPanel->GetButtons().Num() >= 2) {
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[1];
		}
		SetItemInfo(nowItemButton->item_info);
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString(""));
		TextBlock_ItemStat->SetText(FText::FromString(""));
		TextBlock_Description->SetText(FText::FromString(""));
		TextBlock_AddOption->SetText(FText::FromString(""));
		Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
		Item_Type->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
	}
}

void UInventoryWidget::PressedNextButton_Item()
{
	if (UMG_InvnetoryPanel->GetButtons().Num() >= 1) {
		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		previousItemButton = nowItemButton;
		nowItemButton = nextItemButton;

		int32 index = UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);
		if(index != UMG_InvnetoryPanel->GetButtons().Find(GetInvnetoryPanel()->GetButtons().Last()))
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->item_info);
	}
}

void UInventoryWidget::PressedPreviousButton_Item()
{
	if (UMG_InvnetoryPanel->GetButtons().Num() >= 1) {
		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());
		nextItemButton = nowItemButton;
		nowItemButton = previousItemButton;

		int32 index = UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);
		if(index != 0)
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons().Last();
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->item_info);
	}
}

void UInventoryWidget::PressedUpButton_Item()
{
	if (UMG_InvnetoryPanel->GetButtons().Num() >= 7) {
		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());

		//현재 아이템 버튼을 설정
		if(UMG_InvnetoryPanel->GetButtons().Find(nowItemButton) >= 6)
		{
			auto tempButton = UMG_InvnetoryPanel->GetButtons()[UMG_InvnetoryPanel->GetButtons().Find(nowItemButton) - 6];
			nowItemButton = tempButton;
		}
		else
		{
			int32 index = (UMG_InvnetoryPanel->GetButtons().Find(UMG_InvnetoryPanel->GetButtons().Last()) / 6) * 6 + UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);

			if(index > UMG_InvnetoryPanel->GetButtons().Find(UMG_InvnetoryPanel->GetButtons().Last()))
			{
				nowItemButton = UMG_InvnetoryPanel->GetButtons().Last();
			}
			else
			{
				nowItemButton = UMG_InvnetoryPanel->GetButtons()[index];
			}
		}

		//이전 아이템 버튼을 설정
		int32 index = UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);
		if(index != 0)
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons()[UMG_InvnetoryPanel->GetButtons().Find(UMG_InvnetoryPanel->GetButtons().Last())];
		}

		//다음 아이템 버튼을 설정
		if(index != UMG_InvnetoryPanel->GetButtons().Find(UMG_InvnetoryPanel->GetButtons().Last()))
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->item_info);
	}
}

void UInventoryWidget::PressedDownButton_Item()
{
	if (UMG_InvnetoryPanel->GetButtons().Num() >= 7) {
		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetDefaultImage());

		int32 index = UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);
		int32 lastIndex = UMG_InvnetoryPanel->GetButtons().Find(UMG_InvnetoryPanel->GetButtons().Last());
		//현재 아이템 버튼을 설정
		if(index < lastIndex - (lastIndex % 6))
		{
			if(index + 6 <= lastIndex)
			{
				nowItemButton = UMG_InvnetoryPanel->GetButtons()[index + 6];
			}
			else
			{
				nowItemButton = UMG_InvnetoryPanel->GetButtons().Last();
			}
		}
		else
		{
			nowItemButton = UMG_InvnetoryPanel->GetButtons()[index - (lastIndex / 6) * 6];
		}

		//이전 아이템 버튼을 설정
		index = UMG_InvnetoryPanel->GetButtons().Find(nowItemButton);
		if (index != 0)
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons()[index - 1];
		}
		else
		{
			previousItemButton = UMG_InvnetoryPanel->GetButtons()[lastIndex];
		}

		//다음 아이템 버튼을 설정
		if (index != lastIndex)
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[index + 1];
		}
		else
		{
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		}

		nowItemButton->GetImage_button()->SetBrushFromTexture(nowItemButton->GetHoveredImage());
		SetItemInfo(nowItemButton->item_info);
	}
}

class UTexture2D* UInventoryWidget::SetItemTypeImage(EItemType type)
{
	return typeImage[type];
}

void UInventoryWidget::OnInventoryWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	ShowAllEvent();
	previousTypeButton = Button_BattleItem;
	nextTypeButton = Button_Equipment;
	nowTypeButton = Button_All;
	nowTypeButton->WidgetStyle.Normal.SetResourceObject(hoveredImage);

	if (UMG_InvnetoryPanel->GetButtons().Num() != 0) {
		nowItemButton = UMG_InvnetoryPanel->GetButtons()[0];
		previousItemButton = UMG_InvnetoryPanel->GetButtons().Last();
		nowItemButton->GetButton_item()->OnHovered.Broadcast();

		if (UMG_InvnetoryPanel->GetButtons().Num() >= 2) {
			nextItemButton = UMG_InvnetoryPanel->GetButtons()[1];
		}
		//const FIteminfo* temp =nowItemButton->GetButtonItemInfo();
		SetItemInfo(nowItemButton->item_info);
	}
	else
	{
		TextBlock_ItemName->SetText(FText::FromString(""));
		TextBlock_ItemStat->SetText(FText::FromString(""));
		TextBlock_Description->SetText(FText::FromString(""));
		TextBlock_AddOption->SetText(FText::FromString(""));
		Item_Image->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
		Item_Type->SetBrushTintColor(FSlateColor(FLinearColor(0, 0, 0, 0)));
	}
}
