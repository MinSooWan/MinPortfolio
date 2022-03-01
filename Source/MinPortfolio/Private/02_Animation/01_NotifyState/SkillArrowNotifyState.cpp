// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/SkillArrowNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "04_Skill/00_Skill_Attack/00_Arrow/ArrowActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USkillArrowNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	owner = MeshComp->GetOwner<ABaseCharacter>();
	if (owner != nullptr) {
		if (arrowClass != nullptr) {
			auto location = owner->GetMesh()->GetSocketLocation(socketName);
			auto rotation = owner->GetMesh()->GetSocketRotation(socketName);
			spawnArrow = owner->GetWorld()->SpawnActor<AArrowActor>(arrowClass, location, rotation);
		}
	}
}

void USkillArrowNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if(owner != nullptr)
	{
		if(spawnArrow != nullptr)
		{
			spawnArrow->SetActorLocation(owner->GetMesh()->GetSocketLocation(socketName));
			spawnArrow->SetActorRotation(owner->GetMesh()->GetSocketRotation(socketName));
		}
	}
}

void USkillArrowNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (owner != nullptr) {
		if (spawnArrow != nullptr) {
			spawnArrow->SetDamage(damage  + owner->GetStatusComponent()->GetATC());
			if (owner->IsA<APlayerCharacter>()) {
				spawnArrow->GetProjectilMovementComp()->Velocity = (MeshComp->GetOwner<APlayerCharacter>()->target->GetActorLocation() - MeshComp->GetOwner<APlayerCharacter>()->GetActorLocation()) * Speed;
			}
			else if(owner->IsA<AMonsterCharacter>())
			{
				auto lot = Cast<APlayerCharacter>(MeshComp->GetOwner<AMonsterCharacter>()->GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetActorLocation();
				spawnArrow->GetProjectilMovementComp()->Velocity = (lot - MeshComp->GetOwner<AMonsterCharacter>()->GetActorLocation()) * Speed;
			}
		}
	}
}
