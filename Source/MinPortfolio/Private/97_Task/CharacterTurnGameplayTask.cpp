// Fill out your copyright notice in the Description page of Project Settings.


#include "97_Task/CharacterTurnGameplayTask.h"

#include "GameplayTasksComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UCharacterTurnGameplayTask::UCharacterTurnGameplayTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bTickingTask = true;
}

UCharacterTurnGameplayTask* UCharacterTurnGameplayTask::CharacterTurnGameplayTask(ABaseCharacter* taskOwner, ABaseCharacter* targetActor)
{
	UActorComponent* taskComp = nullptr;

	if (taskOwner != nullptr) {
	
		if (taskOwner->FindComponentByClass(UCharacterTurnGameplayTask::StaticClass()) == nullptr)
		{
			auto obj = NewObject<UGameplayTasksComponent>(taskOwner, UGameplayTasksComponent::StaticClass());
			obj->RegisterComponent();

			taskComp = obj;
		}
		else
		{
			taskComp = taskOwner->GetComponentByClass(UGameplayTasksComponent::StaticClass());
		}

		auto task = NewTask<UCharacterTurnGameplayTask>(taskOwner);

		task->owner = taskOwner;
		task->target = targetActor;

		return task;
	}
	else
	{
		return nullptr;
	}
}

void UCharacterTurnGameplayTask::Activate()
{
	Super::Activate();
}

void UCharacterTurnGameplayTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (owner != nullptr && target != nullptr) {
		FRotator rot = (target->GetActorLocation() - owner->GetActorLocation()).Rotation();

		rot.Roll = 0;
		rot.Pitch = 0;

		float Yaw = ((target->GetActorLocation() - owner->GetActorLocation()).Rotation() - owner->GetActorRotation()).Yaw;
		if (Yaw > 180) {
			Yaw -= 360;
		}
		else if (Yaw < -180) {
			Yaw += 360;
		}

		if (0 < Yaw) {
			rot.Yaw = 5;
			if (((target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw - owner->GetActorRotation().Yaw) < 5)
			{
				EndTask();
			}
			else
			{
				owner->AddActorWorldRotation(rot);
			}
		}
		else if (Yaw < 0) {
			rot.Yaw = -5;
			if (((target->GetActorLocation() - owner->GetActorLocation()).Rotation().Yaw - owner->GetActorRotation().Yaw) > 5)
			{
				EndTask();
			}
			else
			{
				owner->AddActorWorldRotation(rot);
			}
		}
	}
}
