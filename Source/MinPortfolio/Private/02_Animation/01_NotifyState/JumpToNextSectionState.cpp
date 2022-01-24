// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/JumpToNextSectionState.h"

#include "00_Character/00_Player/PlayerCharacter.h"

void UJumpToNextSectionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	auto player = MeshComp->GetOwner<APlayerCharacter>();
	if(player != nullptr)
	{
		player->GetMesh()->GetAnimInstance()->Montage_JumpToSection(nextSection);
	}
}
