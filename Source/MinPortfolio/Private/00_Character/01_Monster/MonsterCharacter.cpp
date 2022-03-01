// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "BrainComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "00_Character/01_Monster/00_Controller/MonsterController.h"
#include "01_Item/ItemActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TriggerSphere.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "97_Task/MoveToTarget_Battle_Task.h"
#include "98_Instance/MyGameInstance.h"

AMonsterCharacter::AMonsterCharacter()
{
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCharacterMovement()->MaxWalkSpeed = 200;

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
	if(!GetGameInstance<UMyGameInstance>()->monInfo.monLoc.IsZero())
	{
		if(GetGameInstance<UMyGameInstance>()->monInfo.monLoc == homeLocation && GetGameInstance<UMyGameInstance>()->monInfo.monHp == 0)
		{
			Destroy();
		}
	}
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

	if (bWaitAction == true) {
		if (GetController()->IsA<ABattle_AIController>())
		{
			auto target = GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target");

			if(target != nullptr)
			{
				if(Cast<APlayerCharacter>(target)->GetActionState() == EActionState::NORMAL)
				{
					bWaitAction = false;
					ActionChange();
				}
			}
		}
	}
}

void AMonsterCharacter::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor == moveZone)
	{
		auto target = GetController<AMonsterController>()->GetBlackboardComponent()->GetValueAsObject("Target");
		if (target != nullptr) {
			if (Cast<APlayerCharacter>(target)->GetController()->IsA<ABattleController>()) {

			}
			else
			{
				SetActionState(EActionState::NORMAL);
				GetController<AMonsterController>()->GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
				bMoving = true;
				GetController<AMonsterController>()->GetBrainComponent()->StopLogic("qer");
			}
		}
	}
}

void AMonsterCharacter::ActionChange()
{
	Super::ActionChange();

	if (bAbleAction == false)
	{

		FTimerDelegate timeDel;
		timeDel.BindUFunction(this, FName("ActionChange_Able"));

		GetWorld()->GetTimerManager().SetTimer(AbleAction, timeDel, 9, false);
	}
	else
	{
		auto target = GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target");

		if (Cast<APlayerCharacter>(target)->GetActionState() == EActionState::NORMAL) {
			attackNum = FMath::RandRange(1, 2);
			if (attackNum == 1)
			{
				battleState = EActionState::ATTACK;
				if (attack1_type == EAttackType::RANGED_ATTACK) {
					FTimerDelegate timeDel;
					timeDel.BindUFunction(this, FName("ActionChange_Impossible"));

					GetWorld()->GetTimerManager().SetTimer(ImpossibleAction, timeDel, GetMesh()->GetAnimInstance()->Montage_Play(attack1), false);
				}
				else
				{
					bMoveToTarget = true;

					UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(this, Cast<APlayerCharacter>(target),
						bMoveToTarget, bMoveToStatrLocation, attack1)->ReadyForActivation();
				}
			}
			else if (attackNum == 2)
			{
				battleState = EActionState::ATTACK;
				if (attack2_type == EAttackType::RANGED_ATTACK) {
					FTimerDelegate timeDel;
					timeDel.BindUFunction(this, FName("ActionChange_Impossible"));

					GetWorld()->GetTimerManager().SetTimer(ImpossibleAction, timeDel, GetMesh()->GetAnimInstance()->Montage_Play(attack2), false);
				}
				else
				{
					bMoveToTarget = true;
					UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(this, Cast<APlayerCharacter>(target), bMoveToTarget, bMoveToStatrLocation, attack2)->ReadyForActivation();
				}
			}
		}
		else
		{
			bWaitAction = true;
		}
	}
}

void AMonsterCharacter::ActionChange(float cool)
{
	Super::ActionChange(cool);

	FTimerDelegate timeDel;
	timeDel.BindUFunction(this, FName("ActionChange_Able"));

	GetWorld()->GetTimerManager().SetTimer(AbleAction, timeDel, cool, false);
}

void AMonsterCharacter::ActionChange_Able()
{
	Super::ActionChange_Able();

	ActionChange();
}

void AMonsterCharacter::ActionChange_Impossible()
{
	Super::ActionChange_Impossible();

	EAttackType useAttackType;
	if (attackNum == 1) {
		useAttackType = attack1_type;
	}
	else if(attackNum == 2)
	{
		useAttackType = attack2_type;
	}

	if (useAttackType == EAttackType::MELEE_ATTACK) {
		bMoveToStatrLocation = true;
		SetActorRotation((GetController<AAIController>()->GetBlackboardComponent()->GetValueAsVector("HomeLocation") - GetActorLocation()).Rotation());
	}
	else
	{
		battleState = EActionState::NORMAL;
	}

	ActionChange();
}

void AMonsterCharacter::SetActionState(const EActionState state)
{
	Super::SetActionState(state);

	actionState = state;

	switch (actionState)
	{
	case EActionState::NORMAL:
		if(!GetController()->IsA<ABattle_AIController>())
		{
			
		}
		else {
			GetCharacterMovement()->MaxWalkSpeed = 200;
		}
		break;
	case EActionState::RUN:
		GetCharacterMovement()->MaxWalkSpeed = 400;
		break;
	}
}

void AMonsterCharacter::DropItem()
{
	int32 dropItemCnt = FMath::FRandRange(0, 3);

	TArray<FDropToType*> dropList;
	dropTable->GetAllRows<FDropToType>("", dropList);

	float totalVal = 0;
	for (int32 i = 0; i < dropItemCnt; i++) {
		float randValue = FMath::FRandRange(1, 100);
		for (auto item : dropList) {
			if (item->dropPercent + totalVal >= randValue && totalVal <= randValue) {

				auto spawn = GetWorld()->SpawnActor<AItemActor>(item->dropItem);

				Cast<AMaterialBaseActor>(spawn)->RandomAddOption();
				spawn->SetActorHiddenInGame(true);

				GetGameInstance<UMyGameInstance>()->SetInven(spawn->GetItemInfo<FIteminfo>()->itemActorClass);

				FHaveItemInfo info;
				for (auto x : Cast<AMaterialBaseActor>(spawn)->GetAddOption()) {
					info.materialAddOptions.Add(x);
				}
				info.stat = spawn->GetItemStat();

				GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
				break;
			}
			totalVal += item->dropPercent;
		}
		totalVal = 0;
	}
}
