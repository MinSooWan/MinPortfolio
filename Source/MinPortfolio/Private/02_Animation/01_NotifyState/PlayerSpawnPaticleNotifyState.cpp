// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/PlayerSpawnPaticleNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UPlayerSpawnPaticleNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	APlayerCharacter* player = MeshComp->GetOwner<APlayerCharacter>();
	if(player != nullptr)
	{
		auto location = player->GetActorLocation();
		location.Z = player->GetActorLocation().Z - value;
		UGameplayStatics::SpawnEmitterAtLocation(player, Particle, location, FRotator::ZeroRotator, true);
	}
}
