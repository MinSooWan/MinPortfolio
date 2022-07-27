// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "BrainComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "00_Character/01_Monster/00_Controller/MonsterController.h"
#include "01_Item/ItemActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "03_Widget/05_Battle/UMG_TimeAndHP/TimeAndHpWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TriggerSphere.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "97_Task/MoveToTarget_Battle_Task.h"
#include "98_Instance/MyGameInstance.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/ProgressBar.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonsterCharacter::AMonsterCharacter()
{
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	widgetTimeAndHpComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("time and hp"));
	widgetTimeAndHpComp->SetupAttachment(RootComponent);
	widgetTimeAndHpComp->SetVisibility(false);

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
		if(GetGameInstance<UMyGameInstance>()->monInfo.monLoc == homeLocation && GetGameInstance<UMyGameInstance>()->monInfo.stat.HP == 0)
		{
			GetController<AAIController>()->BrainComponent->StopLogic("Dead");
			GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
			GetMesh()->SetCollisionProfileName("NoCollision");
			SetActorHiddenInGame(true);
		}
		if(GetGameInstance<UMyGameInstance>()->allMonInfo.Num() > 0)
		{
			if (GetGameInstance<UMyGameInstance>()->bInBattle == false) {
				for (auto iter : GetGameInstance<UMyGameInstance>()->allMonInfo)
				{
					if (iter.Key == homeLocation)
					{
						if (iter.Value.bIsDestroy == true)
						{
							GetController<AAIController>()->BrainComponent->StopLogic("Dead");
							GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
							GetMesh()->SetCollisionProfileName("NoCollision");
							SetActorHiddenInGame(true);
							break;
						}
						else {
							statComp->SetAll(this);
							SetActorLocation(iter.Value.monLoc);
							SetActorRotation(iter.Value.monRot);
							break;
						}
					}
				}
			}
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
	if (OtherActor != nullptr) {
		if (GetController() != nullptr) {
			if (OtherActor == moveZone)
			{
				if (GetController()->IsA<AMonsterController>()) {
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

		Cast<UTimeAndHpWidget>(widgetTimeAndHpComp->GetWidget())->InitTime(9);
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

	EAttackType useAttackType = EAttackType::MELEE_ATTACK;
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

	UKismetSystemLibrary::PrintString(this, FString::FromInt(dropItemCnt));

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

void AMonsterCharacter::GiveDamage(float Damage)
{
	Super::GiveDamage(Damage);

	Cast<UTimeAndHpWidget>(widgetTimeAndHpComp->GetWidget())->GetProgressBar_HP()->SetPercent(statComp->GetHP() / statComp->GetMaxHP());

	if (statComp->GetHP() <= 0) {
		Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetMesh()->GetAnimInstance()->StopAllMontages(0);

		//비헤이비어트리 정지
		GetController<ABattle_AIController>()->BrainComponent->StopLogic("Dead");
		GetWorld()->GetTimerManager().ClearTimer(AbleAction);
		GetWorld()->GetTimerManager().ClearTimer(ImpossibleAction);

		if (Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->targets.Num() > 1)
		{
			Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->target = nullptr;

			Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->SetMoveToStart(true);

			/*
			UMoveToTarget_Battle_Task::MoveToTarget_Battle_Task(Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target")), this,
				Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetMoveToTarget(),
				Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetMoveToStatrLocation(),
				hitMontage);
				*/
			FTimerHandle saveHandle;

			FTimerDelegate saveDel;
			saveDel.BindUFunction(this, "MonsterDieToRemove");

			Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->targets.Remove(Cast<AMonsterCharacter>(this));

			Cast<AMonsterCharacter>(this)->DropItem();
			GetWorld()->GetTimerManager().SetTimer(saveHandle, saveDel, GetMesh()->GetAnimInstance()->Montage_Play(Cast<AMonsterCharacter>(this)->GetDieMontage()), false);
		}
		else {
			FTimerHandle saveHandle;

			FTimerDelegate saveDel;
			saveDel.BindUFunction(this, "LoadToLevel");

			Cast<AMonsterCharacter>(this)->DropItem();

			Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->
				GetStatusComponent()->AddEXP(statComp->GetCharacterLevel() * 10);

			GetGameInstance<UMyGameInstance>()->stat = Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"))->GetStatusComponent()->GetCharacterStat();

			GetWorld()->GetTimerManager().SetTimer(saveHandle, saveDel, GetMesh()->GetAnimInstance()->Montage_Play(Cast<AMonsterCharacter>(this)->GetDieMontage()), false);
		}
	}
	else
	{
		if (!GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) {
			GetMesh()->GetAnimInstance()->Montage_Play(hitMontage);
		}
	}
}
