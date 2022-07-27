// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AWeaponBaseActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != nullptr && hitArray.Contains(OtherActor) == false) {
		if (OtherActor->IsA<AMonsterCharacter>()) {
			hitArray.Emplace(OtherActor);

			auto damage = 10;
			if (UsingItemOwner != nullptr) {
				damage = UsingItemOwner->GetStatusComponent()->GetATC() + itemStat.ATC;
			}
			Cast<AMonsterCharacter>(OtherActor)->GiveDamage(damage);

			auto location = Cast<AMonsterCharacter>(OtherActor)->GetMesh()->GetComponentLocation();

			UGameplayStatics::SpawnEmitterAtLocation(this, AttackParticle, location, FRotator::ZeroRotator, true);

			if (addOption.Num() > 0) {
				for (auto iter : addOption)
				{
					switch (iter)
					{
					case EAddOptionsType_Equipment_Weapon::GIVE_BURN:
						Cast<AMonsterCharacter>(OtherActor)->AddDebuffStateCharacter(EDebuffState::GIVE_BURN, 5, 4, EDebuffType::DURATION);
						break;
					case EAddOptionsType_Equipment_Weapon::GIVE_FROZEN:
						Cast<AMonsterCharacter>(OtherActor)->AddDebuffStateCharacter(EDebuffState::GIVE_FROZEN, 5, 9, EDebuffType::DURATION);
						break;
					case EAddOptionsType_Equipment_Weapon::GIVE_DAMAGE:
						Cast<AMonsterCharacter>(OtherActor)->GetStatusComponent()->SetHP(
							FMath::Clamp(Cast<AMonsterCharacter>(OtherActor)->GetStatusComponent()->GetHP() - GetItemInfo<FBattle_Consume>()->damage / 10,
								0.f, Cast<AMonsterCharacter>(OtherActor)->GetStatusComponent()->GetMaxHP()));
						break;
					case EAddOptionsType_Equipment_Weapon::GIVE_SHOCK:
						Cast<AMonsterCharacter>(OtherActor)->AddDebuffStateCharacter(EDebuffState::GIVE_SHOCK, 5, 14, EDebuffType::DURATION);
						break;
					case EAddOptionsType_Equipment_Weapon::GIVE_SLOW:
						Cast<AMonsterCharacter>(OtherActor)->AddDebuffStateCharacter(EDebuffState::GIVE_SLOW, 20, 5, EDebuffType::ONE);
						break;
					}
				}
			}
		}
	}
}

void AWeaponBaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddUniqueDynamic(this, &AWeaponBaseActor::OnActorBeginOverlapEvent);
}

void AWeaponBaseActor::AddOption_Weapon(EAddOptionsType_Equipment_Weapon option)
{
	addOption.Add(option);
}

void AWeaponBaseActor::UseItem(class ABaseCharacter* owner)
{
	Super::UseItem(owner);

	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FWeapon* info = GetItemInfo<FWeapon>();

		if (info != nullptr) {
			AItemActor* spawnItem = Cast<AItemActor>(this);

			spawnItem->SetActorHiddenInGame(true);
			if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) {
				RemoveStat(player, player->GetEquipmentComp()->GetWeaponActor()->GetItemStat());
				Cast<AEquipmentActor>(player->GetEquipmentComp()->GetWeaponActor())->SetEquipped(false);
				ItemChange(player, spawnItem->GetItemInfo<FWeapon>(), spawnItem);
			}
		}
	}

}

void AWeaponBaseActor::ReleaseItem(ABaseCharacter* owner)
{
	if (owner != nullptr) {
		APlayerCharacter* player = Cast<APlayerCharacter>(owner);
		const FWeapon* info = GetItemInfo<FWeapon>();

		if (info != nullptr) {
			AItemActor* spawnItem = Cast<AItemActor>(this);

			if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) {
				RemoveStat(player, spawnItem->GetItemStat());
				if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_WeaponAtcUp"))
				{
					player->GetStatusComponent()->SetATC(player->GetStatusComponent()->GetATC() - 30);
				}

				if (addOption.Num() > 0)
				{
					for (auto iter : addOption)
					{
						switch (iter)
						{
						case EAddOptionsType_Equipment_Weapon::ADD_ATC:
							player->GetStatusComponent()->SetATC(player->GetStatusComponent()->GetATC() - 15);
							break;
						case EAddOptionsType_Equipment_Weapon::ADD_DEF:
							player->GetStatusComponent()->SetDEF(player->GetStatusComponent()->GetDEF() - 15);
							break;
						case EAddOptionsType_Equipment_Weapon::ADD_DEX:
							player->GetStatusComponent()->SetDEX(player->GetStatusComponent()->GetDEX() - 15);
							break;
						case EAddOptionsType_Equipment_Weapon::ADD_HP:
							player->GetStatusComponent()->SetMaxHP(player->GetStatusComponent()->GetMaxHP() - 15);
							player->GetStatusComponent()->SetHP(player->GetStatusComponent()->GetHP() - 15);
							break;
						}
					}
				}
			}
		}
	}
}

AWeaponBaseActor::AWeaponBaseActor()
{
	
}

void AWeaponBaseActor::ClearAddOption()
{
	addOption.Empty();
}

void AWeaponBaseActor::ItemChange(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange(player, info, item);

	auto weapon = player->GetEquipmentComp()->GetWeaponActor();

	if (weapon != nullptr) {

		//player->GetWeaponChildActor()->SetVisibility(true);

		Cast<AEquipmentActor>(item)->SetEquipped(true);

		player->GetEquipmentComp()->SetWeaponActor(*info, item);

		player->GetWeaponChildActor()->AttachToComponent(player->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true),
			SocketName);

		if (item->GetItemInfo<FWeapon>()->swordType == ESwordType::DOUBLE_SWORD)
		{
			player->GetDoubleSwordChild()->SetVisibility(true);
		}
		else
		{
			player->GetDoubleSwordChild()->SetVisibility(false);
		}
		
		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AEquipmentActor>(player->GetWeaponChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(info->mesh);

		player->GetWeaponChildActor()->SetVisibility(false);
		player->GetWeaponChildActor()->SetHiddenInGame(true);
		player->GetWeaponChildActor()->GetChildActor()->SetActorHiddenInGame(true);

		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_WeaponAtcUp"))
		{
			player->GetStatusComponent()->AddATC(30);
		}

		if(addOption.Num() > 0)
		{
			for(auto iter : addOption)
			{
				switch (iter)
				{
				case EAddOptionsType_Equipment_Weapon::ADD_ATC:
					player->GetStatusComponent()->AddATC(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEF:
					player->GetStatusComponent()->AddDEF(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_DEX:
					player->GetStatusComponent()->AddDEX(15);
					break;
				case EAddOptionsType_Equipment_Weapon::ADD_HP:
					player->GetStatusComponent()->AddMaxHP(15);
					player->GetStatusComponent()->AddHP(15);
					break;
				}
			}
		}
		AddStat(player, itemStat);

		weapon = Cast<AWeaponBaseActor>(player->GetWeaponChildActor()->GetChildActor());
		if(weapon != nullptr)
		{
			if (addOption.Num() > 0) {
				for (auto iter : addOption)
				{
					Cast<AWeaponBaseActor>(weapon)->AddOption_Weapon(iter);
				}
			}
		}

		player->SetWeaponEquipped(true);
	}
}

void AWeaponBaseActor::ItemChange_Default(APlayerCharacter* player, const FEquipment* info, AItemActor* item)
{
	Super::ItemChange_Default(player, info, item);

	auto weapon = player->GetEquipmentComp()->GetWeaponActor();

	if (weapon != nullptr) {
		if (player->GetEquipmentComp()->GetWeaponActor() != nullptr) {
			player->GetEquipmentComp()->GetWeaponActor()->Destroy();
		}


		player->GetWeaponChildActor()->SetChildActorClass(info->itemActorClass);
		Cast<AEquipmentActor>(player->GetWeaponChildActor()->GetChildActor())->GetStaticMesh()->SetStaticMesh(info->mesh);

		//player->GetMesh()->SetAnimInstanceClass(item->GetItemInfo<FWeapon>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
		if (player->GetSkillComp()->GetSkillCodes().Contains("Skill_Passive_WeaponAtcUp"))
		{
			player->GetStatusComponent()->SetATC(player->GetStatusComponent()->GetATC() - 30);
		}

		player->SetWeaponEquipped(false);
		player->GetDoubleSwordChild()->SetVisibility(false);
	}
}