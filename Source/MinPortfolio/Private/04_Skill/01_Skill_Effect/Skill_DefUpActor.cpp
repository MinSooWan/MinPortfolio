// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/01_Skill_Effect/Skill_DefUpActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_DefUpActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
	owner->GetStatusComponent()->AddDEF(GetSkillInfo<FSkill_Effect>()->effectValue);
}