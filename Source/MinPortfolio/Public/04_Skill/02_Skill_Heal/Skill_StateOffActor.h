// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/02_Skill_Heal/SkillHealActor.h"
#include "Skill_StateOffActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkill_StateOffActor : public ASkillHealActor
{
	GENERATED_BODY()

public:

	virtual void UseSkill(class ABaseCharacter* target) override;
};
