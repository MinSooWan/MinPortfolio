// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Object/DebuffObject.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"

void UDebuffObject::AddDebuffState(const float value, const float cool, ABaseCharacter* target, EDebuffType type)
{
	Target = target;

	if (Target != nullptr) {
		if (type == EDebuffType::ONE) {
			GiveStatDown(cool, value);
			FTimerDelegate endTimeDel = FTimerDelegate::CreateUObject(target, &ABaseCharacter::RemoveDebuffState, debuff, value, this);
			GetWorld()->GetTimerManager().SetTimer(debuffHandle, endTimeDel, cool, false);
		}
		else {
			FTimerDelegate damageEndTimeDel = FTimerDelegate::CreateUObject(this, &UDebuffObject::GiveDamageDebuff, cool, value);
			GetWorld()->GetTimerManager().SetTimer(damageDebuffHandle, damageEndTimeDel, 1, true);
		}
	}
}

void UDebuffObject::GiveStatDown(const float cool, const float value)
{
	if (Target != nullptr) {
		switch (debuff)
		{
		case EDebuffState::GIVE_ATC_DOWN:
			Target->GetStatusComponent()->SetATC(Target->GetStatusComponent()->GetATC() - value);
			break;
		case EDebuffState::GIVE_DEF_DOWN:
			Target->GetStatusComponent()->SetDEF(Target->GetStatusComponent()->GetDEF() - value);
			break;
		case EDebuffState::GIVE_SLOW:
			Target->GetStatusComponent()->SetDEX(Target->GetStatusComponent()->GetDEX() - value);
			break;
		}
	}
}


void UDebuffObject::GiveDamageDebuff(const float cool,const float value)
{
	if (Target != nullptr) {
		switch (debuff)
		{
		case EDebuffState::GIVE_BURN:
			Target->GetStatusComponent()->SetHP(Target->GetStatusComponent()->GetHP() - value);
			break;
		}

		if (cool == cnt)
		{
			GetWorld()->GetTimerManager().ClearTimer(damageDebuffHandle);
		}
		else
		{
			cnt++;
		}
	}
}
