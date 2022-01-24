// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "StrongShotNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UStrongShotNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditAnywhere)
		class UParticleSystem* loopParticle;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* endParticle;

	UPROPERTY(EditAnywhere)
		FName socketName;

	UPROPERTY()
		class UParticleSystemComponent* particle;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
