// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "CharacterTurnGameplayTask.generated.h"



/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCharacterTurnGameplayTask : public UGameplayTask
{
	GENERATED_BODY()

public:
	UCharacterTurnGameplayTask(const FObjectInitializer& ObjectInitializer);

private:

	UPROPERTY()
		class APlayerCharacter* owner;
	UPROPERTY()
		class AMonsterCharacter* target;

	UPROPERTY()
		FRotator targetRot;

public:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
};
