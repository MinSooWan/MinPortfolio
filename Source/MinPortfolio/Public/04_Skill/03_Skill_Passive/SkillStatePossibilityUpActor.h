// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/03_Skill_Passive/SkillPassiveActor.h"
#include "SkillStatePossibilityUpActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkillStatePossibilityUpActor : public ASkillPassiveActor
{
	GENERATED_BODY()

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;
	
};
