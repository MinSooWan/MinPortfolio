// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/00_Controller/MonsterController.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AMonsterController::AMonsterController()
{
	bAttachToPawn = true;
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("perceptionComponet"));

	UAISenseConfig_Sight* sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sightConfig"));
	sightConfig->SightRadius = 1200.f;
	sightConfig->LoseSightRadius = 1500.f;
	sightConfig->PeripheralVisionAngleDegrees = 45.f;

	FAISenseAffiliationFilter filter;
	filter.bDetectEnemies = true;
	filter.bDetectFriendlies = false;
	filter.bDetectNeutrals = false;

	sightConfig->DetectionByAffiliation = filter;
	sightConfig->SetMaxAge(5.f);
	PerceptionComponent->ConfigureSense(*sightConfig);

	UAISenseConfig_Damage* damageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("damageConfig"));
	damageConfig->SetMaxAge(3.f);
	PerceptionComponent->ConfigureSense(*damageConfig);

	UAISenseConfig_Hearing* hearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("hearingConfig"));
	hearingConfig->HearingRange = 1500.f;
	hearingConfig->bUseLoSHearing = true;
	hearingConfig->LoSHearingRange = 1800.f;
	hearingConfig->DetectionByAffiliation = filter;
	hearingConfig->SetMaxAge(3.f);
	PerceptionComponent->ConfigureSense(*hearingConfig);
}

void AMonsterController::OnPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed()) {
		if (Actor->IsA<APlayerCharacter>()) {

			auto myTeam = GetPawn<ABaseCharacter>()->GetGenericTeamId();
			auto otherTeam = Cast<ABaseCharacter>(Actor)->GetGenericTeamId();

			//적인상태
			if (myTeam != otherTeam) {
				if (GetBlackboardComponent()->GetValueAsObject("Target") == nullptr) {
					GetPawn<AMonsterCharacter>()->SetActionState(EActionState::RUN);
					GetBlackboardComponent()->SetValueAsObject("Target", Actor);
					GetPawn<AMonsterCharacter>()->GetWidgetComp()->SetVisibility(true);
				}
			}
		}
	}
	else
	{
		
	}
}

void AMonsterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMonsterController::OnPerceptionUpdatedEvent);
}

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto monster = Cast<AMonsterCharacter>(InPawn);
	if(monster != nullptr)
	{
		if(monster->GetAiTree() != nullptr)
		{
			RunBehaviorTree(monster->GetAiTree());
			GetBlackboardComponent()->SetValueAsVector("HomeLocation", InPawn->GetActorLocation());
		}
	}
}
