// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/01_Skill_Effect/Skill_DexUpActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_DexUpActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
	owner->GetBuffComp()->AddBuffState(EBuffState::GIVE_DEX_UP, GetSkillInfo<FSkill_Effect>()->effectValue, GetSkillInfo<FSkill_Effect>()->coolTime);
}
