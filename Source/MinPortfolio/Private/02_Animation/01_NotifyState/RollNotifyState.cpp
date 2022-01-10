// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/RollNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void URollNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	player = MeshComp->GetOwner<APlayerCharacter>();

}

void URollNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (player != nullptr) {

		player->SetActionState(EActionState::NORMAL);

	}
}
