// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void ASkillAttackActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	Cast<APlayerCharacter>(owner)->NormalActionState(EActionState::ATTACK);
}
