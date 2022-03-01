// Fill out your copyright notice in the Description page of Project Settings.


#include "97_Task/UseSkill_Sword_GameplayTask.h"

#include "GameplayTasksComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"
#include "GameFramework/CharacterMovementComponent.h"

UUseSkill_Sword_GameplayTask::UUseSkill_Sword_GameplayTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	bTickingTask = true;
}

UUseSkill_Sword_GameplayTask* UUseSkill_Sword_GameplayTask::UseSkill_Sword_GameplayTaskGameplayTask(
	ABaseCharacter* taskOwner, ABaseCharacter* targetActor, ASkillBaseActor* useSkill)
{
	UActorComponent* taskComp = nullptr;

	if(taskOwner != nullptr)
	{
		if(taskOwner->FindComponentByClass(UUseSkill_Sword_GameplayTask::StaticClass()) == nullptr)
		{
			auto obj = NewObject<UGameplayTasksComponent>(taskOwner, UGameplayTasksComponent::StaticClass());
			obj->RegisterComponent();

			taskComp = obj;
		}
		else
		{
			taskComp = taskOwner->GetComponentByClass(UGameplayTasksComponent::StaticClass());
		}

		auto task = NewTask<UUseSkill_Sword_GameplayTask>(taskOwner);

		task->owner = taskOwner;
		task->target = targetActor;
		task->skill = useSkill;

		return task;
	}

	return nullptr;
}

void UUseSkill_Sword_GameplayTask::Activate()
{
	Super::Activate();

	if(owner != nullptr)
	{
		owner->GetCharacterMovement()->MaxWalkSpeed = 1200;
	}
}

void UUseSkill_Sword_GameplayTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (target != nullptr && owner != nullptr && skill != nullptr) {
		auto targetLocation = target->GetActorLocation() - owner->GetActorLocation();
		//UKismetSystemLibrary::PrintString(this, targetLocation.ToString());
		if (target->GetDistanceTo(owner) <= 250)
		{
			skill->EndDynamicFunction();
			EndTask();
		}
		else {
			owner->AddMovementInput(targetLocation);
		}
	}
}
