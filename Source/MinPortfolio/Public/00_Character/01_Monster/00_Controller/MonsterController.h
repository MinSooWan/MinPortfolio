// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterController.generated.h"

UENUM(BlueprintType)
enum class EAIBehaviorType : uint8
{
	APPROCH,
	ATTACK,
	REWARE,

	MAX
};

UENUM(BlueprintType)
enum class EAIMoveType : uint8
{
	WALK,
	RUN,
	FLY,

	MAX
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AMonsterController : public AAIController
{
	GENERATED_BODY()

public:

	AMonsterController();

protected:
	
	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;
};
