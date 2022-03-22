// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AddAPNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UAddAPNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		int32 AddAP;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};
