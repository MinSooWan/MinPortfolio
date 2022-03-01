// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_FatalDriveMagicAttackActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_FatalDriveMagicAttackActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("EndAnimFunction"));

	GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel,
		owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage),
		false);
}

void ASkill_FatalDriveMagicAttackActor::EndAnimFunction()
{
	Super::EndAnimFunction();

	auto num = FMath::RandRange(0, 101);
	if (num >= 40) {
		Cast<APlayerCharacter>(skillOwner)->SetMoveToStatrLocation(true);
		skillTarget->AddDebuffStateCharacter(EDebuffState::GIVE_BURN, 5, 4, EDebuffType::DURATION);
	}
	skillOwner->NormalActionState(EActionState::NORMAL);
}
