// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"
#include "FireArrowShotActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AFireArrowShotActor : public ASkillAttackActor
{
	GENERATED_BODY()

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;
	
};