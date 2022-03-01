// Fill out your copyright notice in the Description page of Project Settings.


#include "97_Task/Task_BattleAction.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UTask_BattleAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto owner = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(owner != nullptr)
	{
		float num = FMath::RandRange(3, 5);
		owner->ActionChange(num);
	}

	return EBTNodeResult::InProgress;
}

void UTask_BattleAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
}
