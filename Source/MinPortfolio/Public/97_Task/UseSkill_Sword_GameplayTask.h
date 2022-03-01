// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "UseSkill_Sword_GameplayTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndTask);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UUseSkill_Sword_GameplayTask : public UGameplayTask
{
	GENERATED_BODY()

public:
	UUseSkill_Sword_GameplayTask(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
		static UUseSkill_Sword_GameplayTask* UseSkill_Sword_GameplayTaskGameplayTask(class ABaseCharacter* taskOwner, class ABaseCharacter* targetActor, class ASkillBaseActor* useSkill);
protected:

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;
	UPROPERTY()
		class ASkillBaseActor* skill;

public:
	UPROPERTY(BlueprintCallable)
		FOnEndTask OnEndTask;

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};