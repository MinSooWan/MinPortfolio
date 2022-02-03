// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/00_Controller/00_Task/Task_MoveToTarget.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	bNotifyTick = true;
	monster = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(monster != nullptr)
	{
		aiCon = monster->GetController<AAIController>();
	}

	return EBTNodeResult::InProgress;
}

void UTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(aiCon != nullptr)
	{
		if (aiCon->GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
		{
			auto target = Cast<ABaseCharacter>(aiCon->GetBlackboardComponent()->GetValueAsObject("Target"));
			switch (aiCon->MoveToLocation(target->GetActorLocation()))
			{
			case EPathFollowingRequestResult::AlreadyAtGoal:
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			case EPathFollowingRequestResult::Failed:
				aiCon->GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
				monster->GetWidgetComp()->SetVisibility(false);
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			case EPathFollowingRequestResult::RequestSuccessful:
				FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
				break;
			}
		}
		else
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
