// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"
#include "Skill_WindAttackActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkill_WindAttackActor : public ASkillAttackActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		float lifeTiem;
	UPROPERTY()
		int32 cnt = 0;
	UPROPERTY()
		FTimerHandle damageHandle;
public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;

	virtual void EndAnimFunction() override;

	UFUNCTION()
		void GiveDamageToTarget();
};
