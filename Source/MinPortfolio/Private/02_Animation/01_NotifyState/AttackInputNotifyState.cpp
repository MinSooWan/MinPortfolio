// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/AttackInputNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"

void UAttackInputNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr) {
		owner = MeshComp->GetOwner<APlayerCharacter>();

		if(owner != nullptr)
		{
			bContinue = false;
		}
	}
}

void UAttackInputNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if(owner != nullptr)
	{
		if(owner->bContinueAttack == true)
		{
			bContinue = true;
		}
	}
}

void UAttackInputNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(owner != nullptr)
	{
		if(nextSection == "End")
		{
			owner->Battle_SetActionState(EActionState::NORMAL);
		}
		else {
			if (bContinue == true)
			{
				owner->GetMesh()->GetAnimInstance()->Montage_JumpToSection(nextSection);
			}
			else
			{
				owner->Battle_SetActionState(EActionState::NORMAL);
				owner->GetMesh()->GetAnimInstance()->StopAllMontages(0.1);
			}
		}
		owner->bContinueAttack = false;
	}
}
