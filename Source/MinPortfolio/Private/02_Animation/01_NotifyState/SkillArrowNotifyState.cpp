// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/SkillArrowNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/00_Skill_Attack/00_Arrow/ArrowActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

void USkillArrowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = MeshComp->GetOwner<APlayerCharacter>();
	if (player != nullptr) {
		if (arrowClass != nullptr) {
			auto location = player->GetMesh()->GetSocketLocation(socketName);
			auto rotation = player->GetMesh()->GetSocketRotation(socketName);
			spawnArrow = player->GetWorld()->SpawnActor<AArrowActor>(arrowClass, location, rotation);

			spawnArrow->GetProjectilMovementComp()->MaxSpeed = Speed;
		}
	}
}

void USkillArrowNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if(player != nullptr)
	{
		if(spawnArrow != nullptr)
		{
			spawnArrow->SetActorLocation(player->GetMesh()->GetSocketLocation(socketName));
			spawnArrow->SetActorRotation(player->GetMesh()->GetSocketRotation(socketName));
		}
	}
}

void USkillArrowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (player != nullptr) {
		if (spawnArrow != nullptr) {
			
			spawnArrow->GetProjectilMovementComp()->Velocity = MeshComp->GetOwner()->GetActorForwardVector() * 500;
		}
	}
}
