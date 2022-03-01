// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillArrowNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillArrowNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AArrowActor> arrowClass;
	UPROPERTY()
		class AArrowActor* spawnArrow;
	UPROPERTY()
		class ABaseCharacter* owner;

	UPROPERTY(EditAnywhere)
		FName socketName;

	UPROPERTY(EditAnywhere)
		float Speed;
	UPROPERTY(EditAnywhere)
		float damage;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};

