// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "FireSwordNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UFireSwordNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UParticleSystem* fireParticle;

	UPROPERTY()
		class UParticleSystemComponent* particle;

	UPROPERTY(EditAnywhere)
		FName socketName;

	UPROPERTY()
		class APlayerCharacter* player;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
