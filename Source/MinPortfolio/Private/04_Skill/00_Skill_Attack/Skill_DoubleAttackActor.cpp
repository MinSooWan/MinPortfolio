// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_DoubleAttackActor.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "97_Task/UseSkill_Sword_GameplayTask.h"
#include "Kismet/KismetSystemLibrary.h"
#include "97_Task/MoveToTarget_Battle_Task.h"

void ASkill_DoubleAttackActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);
	skillOwner->NormalActionState(EActionState::ATTACK);

	UUseSkill_Sword_GameplayTask::UseSkill_Sword_GameplayTaskGameplayTask(owner, target, this)->ReadyForActivation();
}

void ASkill_DoubleAttackActor::EndDynamicFunction()
{
	Super::EndDynamicFunction();

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("EndAnimFunction"));

	auto weapon = Cast<APlayerCharacter>(skillOwner)->GetEquipmentComp()->GetWeaponActor();
	if (weapon->GetItemInfo<FWeapon>()->bIsSword == true)
	{
		switch (weapon->GetItemInfo<FWeapon>()->swordType)
		{
		case ESwordType::DOUBLE_SWORD:
			GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel,
				skillOwner->PlayAnimMontage(Double_Sword_Montage),
				false);
			break;
		case ESwordType::ONE_HAND:
			GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel,
				skillOwner->PlayAnimMontage(One_Hand_Montage),
				false);
			break;
		case ESwordType::TWO_HAND:
			GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel,
				skillOwner->PlayAnimMontage(Two_Hand_Montage),
				false);
			break;
		default:
			break;
		}
	}
}

void ASkill_DoubleAttackActor::EndAnimFunction()
{
	Super::EndAnimFunction();

	Cast<APlayerCharacter>(skillOwner)->SetMoveToStatrLocation(true);

	UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(skillOwner, skillTarget, skillOwner->GetMoveToTarget(),
		skillOwner->GetMoveToStatrLocation(), Double_Sword_Montage)->ReadyForActivation();
}
