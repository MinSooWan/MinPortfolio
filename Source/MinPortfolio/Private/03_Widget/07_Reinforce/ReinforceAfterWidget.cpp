// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceAfterWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/ItemActor.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UReinforceAfterWidget::InitInfo(AItemActor* item)
{
	FString str = "";
	str = TEXT("체력 : ") + FString::FromInt(item->GetItemStat().HP) + "\n" +
		TEXT("공격력 : ") + FString::FromInt(item->GetItemStat().ATC) + "\n" +
		TEXT("방어력 : ") + FString::FromInt(item->GetItemStat().DEF) + "\n" +
		TEXT("민첩성 : ") + FString::FromInt(item->GetItemStat().DEX);
	TextBlock_Stat->SetText(FText::FromString(str));

	str = "";
	if (item->IsA<AArmorBaseActor>()) {
		for (auto iter : Cast<AEquipmentActor>(item)->GetAddOption())
		{
			str += GetAddOptionDescription_Equipment(iter) + "\n";
		}
	}
	else if (item->IsA<AWeaponBaseActor>())
	{
		for (auto iter : Cast<AWeaponBaseActor>(item)->GetAddOption())
		{
			str += GetAddOptionDescription_WeaponItem(iter) + "\n";
		}
	}
	TextBlock_AddOption->SetText(FText::FromString(str));

	Image_item->SetBrushFromSoftTexture(item->GetItemInfo<FIteminfo>()->item_Image);
}

FString UReinforceAfterWidget::GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option)
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

FString UReinforceAfterWidget::GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option)
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

FReply UReinforceAfterWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom) || InKeyEvent.GetKey() == FKey(EKeys::SpaceBar))
	{
		SetVisibility(ESlateVisibility::Hidden);

		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffReinforce();
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}