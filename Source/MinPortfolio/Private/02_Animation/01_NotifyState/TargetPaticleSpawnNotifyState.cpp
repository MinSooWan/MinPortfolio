// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/TargetPaticleSpawnNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UTargetPaticleSpawnNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	APlayerCharacter* player = MeshComp->GetOwner<APlayerCharacter>();
	if(player != nullptr)
	{
		target = player->target;
		if(target != nullptr)
		{
			auto location = target->GetActorLocation();
			location.Z = target->GetActorLocation().Z - value;
			particle = UGameplayStatics::SpawnEmitterAtLocation(target, loopParticle, location);
		}
	}
}

void UTargetPaticleSpawnNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(target != nullptr)
	{
		if(particle != nullptr)
		{
			particle->DestroyComponent();
			auto location = target->GetActorLocation();
			location.Z = target->GetActorLocation().Z - value;
			UGameplayStatics::SpawnEmitterAtLocation(target, endParticle, location);
		}
	}
}
