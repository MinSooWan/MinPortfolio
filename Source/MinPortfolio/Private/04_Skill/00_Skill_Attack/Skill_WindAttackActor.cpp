// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_WindAttackActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"
#include "Components/SphereComponent.h"

void ASkill_WindAttackActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	auto skill = GetWorld()->SpawnActor<ASkillBaseActor>(GetSkillInfo<FSkill>()->skillActorClass, target->GetActorLocation(), FRotator::ZeroRotator);
	if(skill != nullptr)
	{
		FTimerDelegate timeDel;
		timeDel.BindUFunction(this, "EndAnimFunction");

		skill->GetSphereComp()->SetCollisionProfileName(TEXT("NoCollision"));

		FTimerDelegate damageDel;
		damageDel.BindUFunction(this, "GiveDamageToTarget");

		GetWorld()->GetTimerManager().SetTimer(damageHandle, damageDel, 0.5, true);

		owner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo<FSkill_Attack>()->useSkillMontage);

		GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel, lifeTiem, false);
		skill->SetLifeSpan(lifeTiem);
	}
}

void ASkill_WindAttackActor::EndAnimFunction()
{
	Super::EndAnimFunction();

	skillOwner->NormalActionState(EActionState::NORMAL);
}

void ASkill_WindAttackActor::GiveDamageToTarget()
{
	if(cnt < 6)
	{
		cnt++;
		skillTarget->GiveDamage(GetSkillInfo<FSkill_Attack>()->damage);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(damageHandle);
	}
}
