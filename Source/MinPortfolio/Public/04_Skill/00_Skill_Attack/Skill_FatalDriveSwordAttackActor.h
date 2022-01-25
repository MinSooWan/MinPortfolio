// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"
#include "Skill_FatalDriveSwordAttackActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkill_FatalDriveSwordAttackActor : public ASkillAttackActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UAnimMontage* One_Hand_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Two_Hand_Montage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Double_Sword_Montage;

public:

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;
	
};
