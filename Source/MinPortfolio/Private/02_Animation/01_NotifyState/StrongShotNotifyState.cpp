// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/StrongShotNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UStrongShotNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	auto player = MeshComp->GetOwner<APlayerCharacter>();
	if (player != nullptr) {
		auto location = player->GetMesh()->GetSocketLocation(socketName);
		auto rotation = player->GetMesh()->GetSocketRotation(socketName);
		particle = UGameplayStatics::SpawnEmitterAtLocation(player, loopParticle,location, rotation);
	}
}

void UStrongShotNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	auto player = MeshComp->GetOwner<APlayerCharacter>();
	if(player != nullptr)
	{
		if(particle != nullptr)
		{
			particle->DestroyComponent();
			auto location = player->GetMesh()->GetSocketLocation(socketName);
			auto rotation = player->GetMesh()->GetSocketRotation(socketName);
			particle = UGameplayStatics::SpawnEmitterAtLocation(player, endParticle, location, rotation);
		}
	}
}
