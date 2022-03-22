// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "Engine/DataTable.h"
#include "MonsterCharacter.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	RANGED_ATTACK,
	MELEE_ATTACK
};

USTRUCT(BlueprintType)
struct FDropToType : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> dropItem;
	UPROPERTY(EditAnywhere)
		float dropPercent;
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AMonsterCharacter();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATriggerSphere> triggerClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAIController> battle_Controller;

	UPROPERTY()
		class ATriggerSphere* moveZone;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* aiTree;
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* battle_aiTree;

	UPROPERTY(EditAnywhere)
		AActor* targetLocation;
	UPROPERTY()
		bool bMoving = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* widgetComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* widgetTimeAndHpComp;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		FVector homeLocation;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* attack1;
	UPROPERTY(EditAnywhere)
		EAttackType attack1_type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* attack2;
	UPROPERTY(EditAnywhere)
		EAttackType attack2_type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* dieMontage;

	UPROPERTY()
		float attackNum = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EActionState battleState = EActionState::NORMAL;

	UPROPERTY()
		bool bWaitAction = false;

	UPROPERTY(EditAnywhere)
		class UDataTable* dropTable;
	//UTimeAndHpWidget

	UPROPERTY(EditAnywhere)
		int32 MinLevel;

	UPROPERTY(EditAnywhere)
		int32 MaxLevel;

public:
	UPROPERTY()
		FTimerHandle movingHandle;

	FTimerHandle GetMovingHandle() { return movingHandle; }
	bool GetMoving() { return bMoving; }


	class UBehaviorTree* GetAiTree() { return aiTree; }
	class UBehaviorTree* GetBattle_aiTree() { return battle_aiTree; }

	AActor* GetTargetActorLocation() { return targetLocation; }

	UFUNCTION()
		void OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);

	class UWidgetComponent* GetWidgetComp() { return widgetComp; }

	TSubclassOf<class AAIController> GetBattle_Controller() { return battle_Controller; }

	virtual void ActionChange() override;
	virtual void ActionChange(float cool) override;

	virtual void ActionChange_Able() override;
	virtual void ActionChange_Impossible() override;

	virtual void SetActionState(const EActionState state) override;

	EActionState GetBattleState() { return battleState; }
	void SetBattleState(EActionState value) { battleState = value; }

	FVector GetHomeLocation() { return homeLocation; }

	class UAnimMontage* GetDieMontage() { return dieMontage; }

	void DropItem();

	class UWidgetComponent* GetwidgetTimeAndHpComp() { return widgetTimeAndHpComp;  }

	virtual void GiveDamage(float Damage) override;

	const int32 GetMinLevel() { return MinLevel; }
	const int32 GetMaxLevel() { return MaxLevel; }
};
