// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Battle_AIController.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ABattle_AIController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;

	void OnBattleTree();
};
