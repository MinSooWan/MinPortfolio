// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/00_Skill_Attack/SkillAttackActor.h"
#include "Skill_LightningShotActor.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASkill_LightningShotActor : public ASkillAttackActor
{
	GENERATED_BODY()

protected:

	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;

	UPROPERTY(EditAnywhere)
		float lifeTiem;

	UPROPERTY(EditAnywhere)
		float speed;

	UFUNCTION()
		virtual void OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:
	class UParticleSystem* GetHitParticle() { return hitParticle; }

	virtual void UseSkill(class ABaseCharacter* target, class ABaseCharacter* owner) override;

	virtual void EndAnimFunction() override;
};
