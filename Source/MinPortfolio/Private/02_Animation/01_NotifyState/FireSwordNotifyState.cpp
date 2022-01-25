// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/FireSwordNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UFireSwordNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = MeshComp->GetOwner<APlayerCharacter>();
	if (player != nullptr) {
		auto location = player->GetMesh()->GetSocketLocation(socketName);
		auto rotation = player->GetMesh()->GetSocketRotation(socketName);
		particle = UGameplayStatics::SpawnEmitterAtLocation(player, fireParticle, location, rotation);
	}
}

void UFireSwordNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (player != nullptr) {
		auto location = player->GetMesh()->GetSocketLocation(socketName);
		particle->SetRelativeLocation(location);
	}
}

void UFireSwordNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (player != nullptr)
	{
		if (particle != nullptr)
		{
			particle->DestroyComponent();
		}
	}
}
