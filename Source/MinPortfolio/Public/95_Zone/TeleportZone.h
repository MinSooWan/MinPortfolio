// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeleportZone.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ATeleportZone : public ATriggerBox
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FName openLevelName;
	UPROPERTY(EditAnywhere)
		FTransform spawnTransform;
public:
	FName GetOpenLevelName() { return openLevelName; }
	FTransform GetSpawnTransform() { return spawnTransform; }

};
