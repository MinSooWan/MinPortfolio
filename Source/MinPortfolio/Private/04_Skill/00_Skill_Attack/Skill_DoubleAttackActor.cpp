// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_DoubleAttackActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"

void ASkill_DoubleAttackActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	auto weapon = Cast<APlayerCharacter>(owner)->GetEquipmentComp()->GetWeaponActor();
	if(weapon->GetItemInfo<FWeapon>()->bIsSword == true)
	{
		switch (weapon->GetItemInfo<FWeapon>()->swordType)
		{
		case ESwordType::DOUBLE_SWORD:
			owner->PlayAnimMontage(Double_Sword_Montage);
			break;
		case ESwordType::ONE_HAND:
			owner->PlayAnimMontage(One_Hand_Montage);
			break;
		case ESwordType::TWO_HAND:
			owner->PlayAnimMontage(Two_Hand_Montage);
			break;
		default:
			break;
		}
	}
}
