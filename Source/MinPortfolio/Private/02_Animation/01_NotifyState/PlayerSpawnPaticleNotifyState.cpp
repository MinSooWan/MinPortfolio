// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Animation/01_NotifyState/PlayerSpawnPaticleNotifyState.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlayerSpawnPaticleNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	auto owner = MeshComp->GetOwner<ABaseCharacter>();
	if (useType == EUseType::OWNER_TO_OWNER) {
		if (owner != nullptr)
		{
			auto location = owner->GetActorLocation();
			location.Z = owner->GetActorLocation().Z - value;
			UGameplayStatics::SpawnEmitterAtLocation(owner, Particle, location, FRotator::ZeroRotator, true);
		}
	}
	else
	{
		if(owner != nullptr)
		{
			if(owner->IsA<APlayerCharacter>())
			{
				if(Cast<APlayerCharacter>(owner)->target != nullptr)
				{
					auto location = Cast<APlayerCharacter>(owner)->target->GetActorLocation();
					location.Z = owner->GetActorLocation().Z - value;
					UGameplayStatics::SpawnEmitterAtLocation(owner, Particle, location, FRotator::ZeroRotator, true);
				}
			}
			else if(owner->IsA<AMonsterCharacter>())
			{
				if(owner->GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
				{
					auto location = Cast<AActor>(owner->GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetActorLocation();
					location.Z = owner->GetActorLocation().Z - value;
					UGameplayStatics::SpawnEmitterAtLocation(owner, Particle, location, FRotator::ZeroRotator, true);
				}
			}
		}
	}
}
