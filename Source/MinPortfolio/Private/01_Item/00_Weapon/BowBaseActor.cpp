// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Weapon/BowBaseActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"

void ABowBaseActor::UseItem(class ABaseCharacter* target)
{
	Super::UseItem(target);

	if (target != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(target);
		const FWeapon* info = GetItemInfo<FWeapon>();

		if (info != nullptr) {
			if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual("item_Equipment_NoWeapon")) {
				ItemChange(player, info);
			}
			else {
				if (player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->item_Code.IsEqual(info->item_Code)) {
					RemoveStat(player, info->equipmentStat);
					ItemChange_Default(player, player->GetEquipmentComp()->GetDefaultWeaponActor()->GetItemInfo<FWeapon>());
				}
				else {
					RemoveStat(player, player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FWeapon>()->equipmentStat);
					ItemChange(player, info);
				}
			}
		}
	}
}

void ABowBaseActor::ItemChange(APlayerCharacter* player, const FWeapon* info)
{
	Super::ItemChange(player, info);

	UE_LOG(LogTemp, Log, TEXT("111111111111"));
	auto weapon = player->GetBowChildActor()->GetChildActor();

	if (weapon != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("22222222222222"));
		player->GetBowChildActor()->SetVisibility(true);

		player->GetEquipmentComp()->GetWeaponActor()->Destroy();

		AItemActor* spawnItem = GetWorld()->SpawnActor<AItemActor>(info->itemActorClass);
		player->GetEquipmentComp()->SetWeaponActor(*info, spawnItem);

		player->GetBowChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AEquipmentActor>(weapon)->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(info->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
		AddStat(player, info->equipmentStat);

		if (!Cast<AWeaponBaseActor>(player->GetWeaponChildActor()->GetChildActor())->GetItemInfo<FIteminfo>()->item_Code.IsEqual("item_Equipment_NoWeapon")) {
			player->GetWeaponChildActor()->SetVisibility(false);
		}
	}
}

void ABowBaseActor::ItemChange_Default(APlayerCharacter* player, const FWeapon* info)
{
	Super::ItemChange(player, info);

	AActor* weapon = player->GetBowChildActor()->GetChildActor();

	if (weapon != nullptr) {
		if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) {
			player->GetEquipmentComp()->GetWeaponActor()->Destroy();
		}

		player->GetEquipmentComp()->SetWeaponActor(*info, player->GetEquipmentComp()->GetDefaultWeaponActor());

		player->GetBowChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<ABowBaseActor>(weapon)->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetMesh()->SetAnimInstanceClass(info->weaponAnimationBP->GetAnimBlueprintGeneratedClass());

	}
}
