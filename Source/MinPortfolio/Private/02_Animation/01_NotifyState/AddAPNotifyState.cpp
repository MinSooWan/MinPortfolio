// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/AddAPNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"

void UAddAPNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	auto owner = MeshComp->GetOwner<APlayerCharacter>();

	if(owner != nullptr)
	{
		owner->GetStatusComponent()->AddActionsPoint(AddAP);
	}
}
