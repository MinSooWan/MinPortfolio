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
		skill->GetSphereComp()->SetCollisionProfileName(TEXT("NoCollision"));
		owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
		skill->SetLifeSpan(lifeTiem);
	}
}
