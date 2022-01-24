// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/01_Skill_Effect/SkillEffectActor.h"
#include "Skill_DefUpActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkill_DefUpActor : public ASkillEffectActor
{
	GENERATED_BODY()

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;
};
