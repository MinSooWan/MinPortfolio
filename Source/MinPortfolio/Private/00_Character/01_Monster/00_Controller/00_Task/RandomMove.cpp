// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/00_Controller/00_Task/RandomMove.h"

#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/MonsterController.h"
#include "NavigationSystem.h"

EBTNodeResult::Type URandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	monster = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if(monster != nullptr)
	{
		if(!monster->GetWorld()->GetTimerManager().IsTimerActive(monster->GetMovingHandle()))
		{
			aiCon = monster->GetController<AAIController>();
			float time = FMath::RandRange(1, 5);
			monster->SetMoving(true);
			
		}
	}

	return EBTNodeResult::InProgress;
}

void URandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(monster != nullptr)
	{

		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(monster, monster->GetActorLocation(),  );
	//	auto result = aiCon->MoveToLocation()
	}
	
}
