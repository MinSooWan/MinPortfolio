// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/02_Skill_Heal/Skill_HpHealActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_HpHealActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
	owner->GetStatusComponent()->AddHP(GetSkillInfo<FSkill_Heal>()->heal);
}
