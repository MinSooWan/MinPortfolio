// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PickUpNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UPickUpNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		class APlayerCharacter* owner;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
