// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackInputNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UAttackInputNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class APlayerCharacter* owner;

	UPROPERTY(EditAnywhere)
		FName nextSection;

	UPROPERTY()
		bool bContinue;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
