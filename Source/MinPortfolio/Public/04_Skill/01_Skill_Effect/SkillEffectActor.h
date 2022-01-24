// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillBaseActor.h"
#include "SkillEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkillEffectActor : public ASkillBaseActor
{
	GENERATED_BODY()

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;
};
