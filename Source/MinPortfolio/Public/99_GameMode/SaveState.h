// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SaveState.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ASaveState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> saveActors;
};
