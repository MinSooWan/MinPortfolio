// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/09_Combination/Combination_Able_Main.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/09_Combination/CombinationMainWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "03_Widget/09_Combination/Combination_Able_OptionButton.h"
#include "Components/VerticalBox.h"

void UCombination_Able_Main::OnComAbleWidget(const FIteminfo* info)
{
	VerticalBox_AddOption->ClearChildren();

	//image
	item_image->SetBrushFromTexture(info->item_Image);

	//stat
	FString str = "";
	float atc = 0;
	float def = 0;
	float dex = 0;
	float hp = 0;
	for(auto iter : GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetApplyItemList())
	{
		atc += iter->GetItemStat().ATC;
		def += iter->GetItemStat().DEF;
		dex += iter->GetItemStat().DEX;
		hp += iter->GetItemStat().MaxHP;
	}

	str = TEXT("공격력 : ") + FString::FromInt(atc) + "\n" + TEXT("방어력 : ") + FString::FromInt(def) + "\n" + TEXT("민첩성 : ") + FString::FromInt(dex) + "\n" +
		TEXT("체력 : ") + FString::FromInt(hp) + "\n";
	TextBlock_ItemStat->SetText(FText::FromString(str));

	//addOption

	auto SPitem = GetOwningPlayer()->GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);
	for(auto iter : GetOwningPlayer<ACustomController>()->GetMainWidget()->GetUMG_CombinationMain()->GetApplyItemList())
	{
		for(auto x : Cast<AMaterialBaseActor>(iter)->GetAddOption())
		{
			if(SPitem->IsA<AWeaponBaseActor>())
			{
				if(IsWeaponAddOption(x))
				{
					auto button = CreateWidget<UCombination_Able_OptionButton>(GetOwningPlayer(), buttonClass);
					if (button != nullptr)
					{
						button->SetButtonOption(x);
						VerticalBox_AddOption->AddChild(button);
					}
				}
			}
			else if(SPitem->IsA<AArmorBaseActor>())
			{
				if(IsArmorAddOption(x))
				{
					auto button = CreateWidget<UCombination_Able_OptionButton>(GetOwningPlayer(), buttonClass);
					if (button != nullptr)
					{
						button->SetButtonOption(x);
						VerticalBox_AddOption->AddChild(button);
					}
				}
			}
		}
	}
	SPitem->Destroy();
}

bool UCombination_Able_Main::IsWeaponAddOption(EAddOptionsType_Material option)
{
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		return true;
	case EAddOptionsType_Material::ADD_DEF:
		return true;
	case EAddOptionsType_Material::ADD_DEX:
		return true;
	case EAddOptionsType_Material::ADD_HP:
		return true;
	case EAddOptionsType_Material::ADD_ITEM:
		return true;
	case EAddOptionsType_Material::ADD_EXP:
		return true;
	case EAddOptionsType_Material::GIVE_DAMAGE:
		return true;
	case EAddOptionsType_Material::GIVE_BURN:
		return true;
	case EAddOptionsType_Material::GIVE_FROZEN:
		return true;
	case EAddOptionsType_Material::GIVE_SHOCK:
		return true;
	case EAddOptionsType_Material::GIVE_SLOW:
		return true;
	}
	return false;
}

bool UCombination_Able_Main::IsArmorAddOption(EAddOptionsType_Material option)
{
	switch (option)
	{
	case EAddOptionsType_Material::ADD_ATC:
		return true;
	case EAddOptionsType_Material::ADD_DEF:
		return true;
	case EAddOptionsType_Material::ADD_DEX:
		return true;
	case EAddOptionsType_Material::ADD_HP:
		return true;
	case EAddOptionsType_Material::ADD_ITEM:
		return true;
	case EAddOptionsType_Material::ADD_EXP:
		return true;
	}
	return false;
}
