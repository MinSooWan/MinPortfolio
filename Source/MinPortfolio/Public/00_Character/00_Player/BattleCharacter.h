// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "BattleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API ABattleCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	ABattleCharacter();

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PressedBattle_Attack();
};
