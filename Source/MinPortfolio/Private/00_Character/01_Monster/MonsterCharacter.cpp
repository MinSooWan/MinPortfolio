// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "BrainComponent.h"
#include "00_Character/01_Monster/00_Controller/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TriggerSphere.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMonsterCharacter::AMonsterCharacter()
{
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->MaxWalkSpeed = 400;

	GetMesh()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_Yes;

	SetGenericTeamId(FGenericTeamId(5));

	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("widget"));
	widgetComp->SetupAttachment(RootComponent);
	widgetComp->SetVisibility(false);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	moveZone = GetWorld()->SpawnActor<ATriggerSphere>(triggerClass, GetActorLocation(), FRotator::ZeroRotator);
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorEndOverlap.AddDynamic(this, &AMonsterCharacter::OnActorEndOverlapEvent);
	homeLocation = GetActorLocation();
}

void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bMoving)
	{
		switch (GetController<AMonsterController>()->MoveToLocation(homeLocation))
		{
		case EPathFollowingRequestResult::AlreadyAtGoal:
			bMoving = false;
			GetController<AMonsterController>()->RunBehaviorTree(aiTree);
			widgetComp->SetVisibility(false);
			break;
		case EPathFollowingRequestResult::Failed:
			
			break;
		case EPathFollowingRequestResult::RequestSuccessful:

			break;
		}
	}
}

void AMonsterCharacter::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor == moveZone)
	{
		GetController<AMonsterController>()->GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
		bMoving = true;
		GetController<AMonsterController>()->GetBrainComponent()->StopLogic("qer");
	}
}
