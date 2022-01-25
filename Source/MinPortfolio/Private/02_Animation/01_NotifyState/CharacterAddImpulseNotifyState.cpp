// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/CharacterAddImpulseNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAddImpulseNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = MeshComp->GetOwner<APlayerCharacter>();
	if(player != nullptr)
	{
		FVector pos = FVector(X, Y, Z);
		player->GetCharacterMovement()->AddImpulse(pos, true);
	}
}

void UCharacterAddImpulseNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
