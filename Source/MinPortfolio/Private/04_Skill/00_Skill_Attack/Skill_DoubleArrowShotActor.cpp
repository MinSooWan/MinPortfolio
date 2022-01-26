// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_DoubleArrowShotActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_DoubleArrowShotActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);
	owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
}