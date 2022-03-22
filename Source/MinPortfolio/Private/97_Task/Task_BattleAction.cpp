// Fill out your copyright notice in the Description page of Project Settings.


#include "97_Task/Task_BattleAction.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "03_Widget/05_Battle/UMG_TimeAndHP/TimeAndHpWidget.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

EBTNodeResult::Type UTask_BattleAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto owner = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(owner != nullptr)
	{
		float num = FMath::RandRange(3, 9);

		owner->GetwidgetTimeAndHpComp()->SetVisibility(true);
		Cast<UTimeAndHpWidget>(owner->GetwidgetTimeAndHpComp()->GetWidget())->InitTime(num);
		Cast<UTimeAndHpWidget>(owner->GetwidgetTimeAndHpComp()->GetWidget())->GetProgressBar_HP()->SetPercent(owner->GetStatusComponent()->GetHP() / owner->GetStatusComponent()->GetMaxHP());
		owner->ActionChange(num);
	}

	return EBTNodeResult::InProgress;
}

void UTask_BattleAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
}
