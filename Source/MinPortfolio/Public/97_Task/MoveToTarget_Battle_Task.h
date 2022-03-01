// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "MoveToTarget_Battle_Task.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMoveToTarget_Battle_Task : public UGameplayTask
{
	GENERATED_BODY()

public:
	UMoveToTarget_Battle_Task(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		/// <summary>
		/// 
		/// </summary>
		/// <param name="taskOwner"></param>
		/// <param name="targetActor"></param>
		/// <param name="MoveToTarget"></param>
		/// <param name="MoveToStartLoction"></param>
		/// <param name="attackMontage">Monster Only Use Param</param>
		/// <returns></returns>
		static UMoveToTarget_Battle_Task* MoveToTarget_Battle_Task(class ABaseCharacter* taskOwner, class ABaseCharacter* targetActor,
			bool MoveToTarget, bool MoveToStartLoction, class UAnimMontage* attackMontage);
private:

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;
	UPROPERTY()
		bool bMoveTarget;
	UPROPERTY()
		bool bMoveStart;
	UPROPERTY()
		class UAnimMontage* montage;

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};
