// Fill out your copyright notice in the Description page of Project Settings.


#include "97_Task/MoveToTarget_Battle_Task.h"

#include "AIController.h"
#include "GameplayTasksComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UMoveToTarget_Battle_Task::UMoveToTarget_Battle_Task(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bTickingTask = true;
}

UMoveToTarget_Battle_Task* UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(ABaseCharacter* taskOwner,
	ABaseCharacter* targetActor, bool MoveToTarget, bool MoveToStartLoction, UAnimMontage* attackMontage)
{
	UActorComponent* taskComp = nullptr;

	if (taskOwner != nullptr && targetActor != nullptr) {

		if (taskOwner->FindComponentByClass(UMoveToTarget_Battle_Task::StaticClass()) == nullptr)
		{
			auto obj = NewObject<UGameplayTasksComponent>(taskOwner, UGameplayTasksComponent::StaticClass());
			obj->RegisterComponent();

			taskComp = obj;
		}
		else
		{
			taskComp = taskOwner->GetComponentByClass(UGameplayTasksComponent::StaticClass());
		}

		auto task = NewTask<UMoveToTarget_Battle_Task>(taskOwner);

		task->owner = taskOwner;
		task->target = targetActor;
		task->bMoveTarget = MoveToTarget;
		task->bMoveStart = MoveToStartLoction;
		task->montage = attackMontage;

		return task;
	}
	else
	{
		return nullptr;
	}
}

void UMoveToTarget_Battle_Task::Activate()
{
	Super::Activate();
}

void UMoveToTarget_Battle_Task::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (owner->GetMoveToTarget() == true)
	{
		auto targetLocation = target->GetActorLocation() - owner->GetActorLocation();
		//UKismetSystemLibrary::PrintString(this, targetLocation.ToString());
		if (target->GetDistanceTo(owner) <= owner->GetDistanceValue())
		{
			if (owner->IsA<APlayerCharacter>()) {
				bMoveStart = true;
				bMoveTarget = false;
				owner->SetMoveToTarget(false);
				Cast<APlayerCharacter>(owner)->Battle_SetActionState(EActionState::ATTACK);
			}
			else if (owner->IsA<AMonsterCharacter>())
			{
				if (target->GetActionState() == EActionState::NORMAL) {
					bMoveStart = true;
					bMoveTarget = false;
					owner->SetMoveToTarget(false);
					FTimerDelegate timeDel;
					timeDel.BindUFunction(Cast<AMonsterCharacter>(owner), FName("ActionChange_Impossible"));

					owner->GetWorld()->GetTimerManager().SetTimer(owner->GetImpossibleActionHandle(), timeDel, owner->GetMesh()->GetAnimInstance()->Montage_Play(montage), false);
				}
			}
		}
		else {
			if(owner->IsA<AMonsterCharacter>())
			{
				if(target->GetActionState() == EActionState::NORMAL)
				{
					owner->AddMovementInput(targetLocation);
				}
			}
			else
			{
				owner->AddMovementInput(targetLocation);
			}
		}

		//GetMovementComponent()->Velocity = (target->GetActorLocation() - GetActorLocation());
	}

	if (owner->GetMoveToStatrLocation() == true)
	{
		if (owner->IsA<APlayerCharacter>()) {
			auto location = owner->GetStartLocation() - owner->GetActorLocation();
			//UKismetSystemLibrary::PrintString(this, location.ToString());

			if (location.X >= -0.1f)
			{
				bMoveStart = false;
				owner->SetMoveToStart(false);
				if (target != nullptr)
				{
					Cast<APlayerCharacter>(owner)->Battle_SetActionState(EActionState::NORMAL);
					if(Cast<APlayerCharacter>(owner)->target == nullptr)
					{
						Cast<APlayerCharacter>(owner)->targetChange_right();
						
						Cast<APlayerCharacter>(owner)->ActionChange_Impossible();
					}
					else {
						owner->SetActorRotation((target->GetActorLocation() - owner->GetActorLocation()).Rotation());
					}
					EndTask();
				}
			}
			else
			{
				owner->AddMovementInput(location);
			}
		}
		else if(owner->IsA<AMonsterCharacter>())
		{
			auto location = owner->GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsVector("HomeLocation") - owner->GetActorLocation();

			if (location.X <= -0.1f)
			{
				bMoveStart = false;
				owner->SetMoveToStart(false);
				if (target != nullptr)
				{
					owner->SetActorRotation((Cast<APlayerCharacter>(target)->GetStartLocation() - owner->GetActorLocation()).Rotation());
					Cast<AMonsterCharacter>(owner)->SetBattleState(EActionState::NORMAL);
					EndTask();
				}
			}
			else
			{
				owner->AddMovementInput(location);
			}
		}
	}
}
