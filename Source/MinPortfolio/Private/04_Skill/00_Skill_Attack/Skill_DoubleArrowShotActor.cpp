// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_DoubleArrowShotActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_DoubleArrowShotActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, "EndAnimFunction");

	GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel, owner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo<FSkill>()->useSkillMontage), false);
}

void ASkill_DoubleArrowShotActor::EndAnimFunction()
{
	Super::EndAnimFunction();

	skillOwner->NormalActionState(EActionState::NORMAL);
}
