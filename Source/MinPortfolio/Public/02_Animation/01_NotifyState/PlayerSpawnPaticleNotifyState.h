// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PlayerSpawnPaticleNotifyState.generated.h"

UENUM(BlueprintType)
enum class EUseType : uint8
{
	OWNER_TO_OWNER,
	OWNER_TO_TARGET
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UPlayerSpawnPaticleNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere)
		float value;

	UPROPERTY(EditAnywhere)
		EUseType useType;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
};
