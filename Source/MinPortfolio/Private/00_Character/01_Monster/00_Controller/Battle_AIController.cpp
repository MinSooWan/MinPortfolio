 // Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"

#include "00_Character/01_Monster/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void ABattle_AIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABattle_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto monster = Cast<AMonsterCharacter>(InPawn);
	if (monster != nullptr)
	{
		if (monster->GetAiTree() != nullptr)
		{
			RunBehaviorTree(monster->GetBattle_aiTree());
			GetBlackboardComponent()->SetValueAsVector("HomeLocation", InPawn->GetActorLocation());

		}
	}
}
