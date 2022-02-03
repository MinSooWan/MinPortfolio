// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Task_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UTask_MoveToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class AMonsterCharacter* monster;
	UPROPERTY()
		class AAIController* aiCon;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
