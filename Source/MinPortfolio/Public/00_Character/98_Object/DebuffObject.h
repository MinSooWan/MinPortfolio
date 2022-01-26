// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DebuffObject.generated.h"

UENUM(BlueprintType)
enum class EDebuffState : uint8
{
	NORMAL,
	GIVE_BURN,
	GIVE_FROZEN,
	GIVE_SHOCK,
	GIVE_SLOW,
	GIVE_ATC_DOWN,
	GIVE_DEF_DOWN
};

UENUM(BlueprintType)
enum class EDebuffType : uint8
{
	DURATION,
	ONE
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UDebuffObject : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
		float cnt = 0;

	UPROPERTY()
		FTimerHandle debuffHandle;

	UPROPERTY()
		FTimerHandle damageDebuffHandle;

	UPROPERTY()
		class ABaseCharacter* Target;

	UPROPERTY()
		EDebuffState debuff;

public:
	void SetDebuff(EDebuffState value) { debuff = value; }

	void AddDebuffState(const float value, const float cool, class ABaseCharacter* target, EDebuffType type);

	void GiveStatDown(const float cool, const float value);

	UFUNCTION()
		void GiveDamageDebuff(const float cool, const float value);
};
