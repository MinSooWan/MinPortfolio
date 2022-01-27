// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Components/ChildActorComponent.h"

void AArmorBaseActor::UseItem(class ABaseCharacter* owner)
{
	Super::UseItem(owner);

	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FArmor* info = GetItemInfo<FArmor>();

		if (info != nullptr) {
			AItemActor* spawnItem = GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);
			if (player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FArmor>()->item_Code.IsEqual("item_Equipment_NoArmor")) {
				ItemChange(player, spawnItem->GetItemInfo<FArmor>(), spawnItem);
			}
			else {
				if (player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FArmor>()->item_Code.IsEqual(info->item_Code)) {
					RemoveStat(player, info->equipmentStat);
					ItemChange_Default(player, player->GetEquipmentComp()->GetDefaultArmorActor()->GetItemInfo<FArmor>(), player->GetEquipmentComp()->GetDefaultArmorActor());
				}
				else {
					if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
					{
						player->GetStatusComponent()->SetDEF(player->GetStatusComponent()->GetDEF() - 30);
					}
					RemoveStat(player, player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FArmor>()->equipmentStat);
					ItemChange(player, spawnItem->GetItemInfo<FArmor>(), spawnItem);
				}
			}

			spawnItem->Destroy();
		}
	}
}

void AArmorBaseActor::ItemChange(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange(player, info, item);

	auto armor = player->GetEquipmentComp()->GetArmorActor();

	if (armor != nullptr) {

		player->GetEquipmentComp()->GetArmorActor()->Destroy();

		player->GetEquipmentComp()->SetArmorActor(*info, item);

		UE_LOG(LogTemp, Log, TEXT("111111111111"));
		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_ArmorDefUp"))
		{
			UE_LOG(LogTemp, Log, TEXT("2222222222"));
			player->GetStatusComponent()->AddDEF(30);
		}

		AddStat(player, info->equipmentStat);

		player->SetArmorEquipped(true);
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

		player->GetEquipmentComp()->SetArmorActor(*info, player->GetEquipmentComp()->GetDefaultArmorActor());

		player->SetArmorEquipped(false);
	}
}
