// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/00_Controller/00_Task/RandomMove.h"

#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/MonsterController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type URandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	monster = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	bNotifyTick = true;
	if(monster != nullptr)
	{
		//UKismetSystemLibrary::PrintString(monster, "ExecuteTask");
		if(!monster->GetWorld()->GetTimerManager().IsTimerActive(monster->movingHandle))
		{
			aiCon = monster->GetController<AAIController>();
			float time = FMath::RandRange(1, 5);

			monster->GetWorld()->GetTimerManager().SetTimer(monster->movingHandle, FTimerDelegate(), time, false);
			auto location = OwnerComp.GetBlackboardComponent()->GetValueAsVector("HomeLocation");
			UNavigationSystemV1::K2_GetRandomReachablePointInRadius(monster, location, result, 1500);
		}
	}

	return EBTNodeResult::InProgress;
}

void URandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(monster != nullptr)
	{
		if(aiCon->GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
		{
			monster->GetWorld()->GetTimerManager().ClearTimer(monster->movingHandle);
			monster->GetWidgetComp()->SetVisibility(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}

		switch (aiCon->MoveToLocation(result))
		{
		case EPathFollowingRequestResult::AlreadyAtGoal:
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		case EPathFollowingRequestResult::Failed:
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		case EPathFollowingRequestResult::RequestSuccessful:
			FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
			break;
		}
	}
	
}
