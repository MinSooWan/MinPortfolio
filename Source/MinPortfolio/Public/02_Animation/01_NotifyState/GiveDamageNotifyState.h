// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GiveDamageNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UGiveDamageNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		float damage;
	UPROPERTY(EditAnywhere)
		bool bIsDefaultAttack = false;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};
