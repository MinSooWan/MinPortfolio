// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipment/ShoesBaseActor.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"

void AShoesBaseActor::ItemChange(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange(player, info, item);

	auto armor = player->GetEquipmentComp()->GetShoesActor();

	if (armor != nullptr) {

		player->GetEquipmentComp()->GetShoesActor()->Destroy();

		Cast<AEquipmentActor>(item)->SetEquipped(true);

		player->GetEquipmentComp()->SetShoesActor(*info, item);

		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
		{
			player->GetStatusComponent()->AddDEF(30);
		}

		AddStat(player, itemStat);
	}
}

void AShoesBaseActor::ItemChange_Default(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange_Default(player, info, item);

	auto armor = player->GetEquipmentComp()->GetShoesActor();

	if (armor != nullptr) {
		if (player->GetEquipmentComp()->GetShoesActor() != nullptr) {
			player->GetEquipmentComp()->GetShoesActor()->Destroy();
		}
		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
		{
			player->GetStatusComponent()->SetDEF(player->GetStatusComponent()->GetDEF() - 30);
		}
	}
}

void AShoesBaseActor::AddOption(EAddOptionsType_Equipment option)
{
	Super::AddOption(option);
}

void AShoesBaseActor::UseItem(ABaseCharacter* owner)
{
	Super::UseItem(owner);

	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FArmor* info = GetItemInfo<FArmor>();

		if (info != nullptr) {
			AItemActor* spawnItem = Cast<AItemActor>(player->GetInventoryComp()->FindItem(this));
			if (spawnItem != nullptr) {

				Cast<AEquipmentActor>(player->GetEquipmentComp()->GetShoesActor())->SetEquipped(false);
				RemoveStat(player, player->GetEquipmentComp()->GetShoesActor()->GetItemStat());
				ItemChange(player, spawnItem->GetItemInfo<FArmor>(), spawnItem);
			}
		}
	}
}
