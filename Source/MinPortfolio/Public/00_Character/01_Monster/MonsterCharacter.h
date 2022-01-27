// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API AMonsterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AMonsterCharacter();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* aiTree;
	UPROPERTY(EditAnywhere)
		AActor* targetLocation;

public:

	class UBehaviorTree* GetAiTree() { return aiTree; }
	AActor* GetTargetLocation() { return targetLocation; }
};
