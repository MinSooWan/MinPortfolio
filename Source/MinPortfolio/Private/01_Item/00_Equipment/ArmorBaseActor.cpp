// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void AArmorBaseActor::UseItem(class ABaseCharacter* owner)
{
	Super::UseItem(owner);

	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FArmor* info = GetItemInfo<FArmor>();

		if (info != nullptr) {
			AItemActor* spawnItem = Cast<AItemActor>(this);

			if (spawnItem != nullptr) {
				Cast<AEquipmentActor>(player->GetEquipmentComp()->GetArmorActor())->SetEquipped(false);
				RemoveStat(player, player->GetEquipmentComp()->GetArmorActor()->GetItemStat());
				ItemChange(player, spawnItem->GetItemInfo<FArmor>(), spawnItem);
			}
		}
	}
}

void AArmorBaseActor::ClearAddOption()
{
	addOption.Empty();
}

void AArmorBaseActor::ItemChange(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange(player, info, item);

	auto armor = player->GetEquipmentComp()->GetArmorActor();

	if (armor != nullptr) {

		player->GetEquipmentComp()->GetArmorActor()->Destroy();

		Cast<AEquipmentActor>(item)->SetEquipped(true);

		player->GetEquipmentComp()->SetArmorActor(*info, item);

		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
		{
			player->GetStatusComponent()->AddDEF(30);
		}

		if (addOption.Num() > 0)
		{
			for (auto iter : addOption)
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment::ADD_ATC:
					player->GetStatusComponent()->AddATC(15);
					break;
				case EAddOptionsType_Equipment::ADD_DEF:
					player->GetStatusComponent()->AddDEF(15);
					break;
				case EAddOptionsType_Equipment::ADD_DEX:
					player->GetStatusComponent()->AddDEX(15);
					break;
				case EAddOptionsType_Equipment::ADD_HP:
					player->GetStatusComponent()->AddMaxHP(15);
					player->GetStatusComponent()->AddHP(15);
					break;
				}
			}
		}

		AddStat(player, itemStat);

	}
}

void AArmorBaseActor::ItemChange_Default(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange_Default(player, info, item);

	auto armor = player->GetEquipmentComp()->GetArmorActor();

	if (armor != nullptr) {
		if (player->GetEquipmentComp()->GetArmorActor() != nullptr) {
			player->GetEquipmentComp()->GetArmorActor()->Destroy();
		}
		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
		{
			player->GetStatusComponent()->SetDEF(player->GetStatusComponent()->GetDEF() - 30);
		}

	}
}

void AArmorBaseActor::AddOption(EAddOptionsType_Equipment option)
{
	Super::AddOption(option);
}
