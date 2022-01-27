// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/02_Skill_Heal/Skill_StateOffActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "04_Skill/SkillInfomation.h"

void ASkill_StateOffActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);

	if(owner->GetDebuffs().Num() >= 1)
	{
		for(auto iter : owner->GetDebuffs())
		{
			switch (*iter->Getdebuff())
			{
			case EDebuffState::GIVE_ATC_DOWN:
				owner->GetStatusComponent()->AddATC(iter->GetEffectValue());
				break;
			case EDebuffState::GIVE_DEF_DOWN:
				owner->GetStatusComponent()->AddDEF(iter->GetEffectValue());
				break;
			case EDebuffState::GIVE_SLOW:
				owner->GetStatusComponent()->AddDEX(iter->GetEffectValue());
				break;
			}


			if(GetWorld()->GetTimerManager().IsTimerActive(*iter->GetDebuffHandle()))
			{
				GetWorld()->GetTimerManager().ClearTimer(*iter->GetDebuffHandle());
			}
			else if(GetWorld()->GetTimerManager().IsTimerActive(*iter->GetDamageDebuffHandle()))
			{
				GetWorld()->GetTimerManager().ClearTimer(*iter->GetDamageDebuffHandle());
			}
			owner->RemoveDebuffObejct(iter);
			iter->ConditionalBeginDestroy();
		}
	}
}
