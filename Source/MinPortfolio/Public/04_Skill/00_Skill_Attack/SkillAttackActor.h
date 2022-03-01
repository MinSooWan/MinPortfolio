// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillBaseActor.h"
#include "SkillAttackActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkillAttackActor : public ASkillBaseActor
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		FTimerHandle endSkillHandle;

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;

	virtual void EndDynamicFunction() override { }

	UFUNCTION()
		virtual void EndAnimFunction() { }
};
