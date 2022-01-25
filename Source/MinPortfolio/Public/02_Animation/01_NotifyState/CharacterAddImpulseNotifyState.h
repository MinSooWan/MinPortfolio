// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CharacterAddImpulseNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCharacterAddImpulseNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class APlayerCharacter* player;

	UPROPERTY(EditAnywhere)
		FName animType;

	UPROPERTY(EditAnywhere)
		float X;
	UPROPERTY(EditAnywhere)
		float Y;
	UPROPERTY(EditAnywhere)
		float Z;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};
