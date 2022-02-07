// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/TargetPoint.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		TSubclassOf<class AMonsterCharacter> target;

	UPROPERTY(EditAnywhere)
		TArray<FTransform> targetPoint;

	UPROPERTY()
		TSubclassOf<class AItemActor> weapon;
	UPROPERTY()
		TSubclassOf<class AItemActor> armor;
	UPROPERTY()
		TSubclassOf<class AItemActor> tool;
	UPROPERTY()
		TArray<TSubclassOf<class ASkillBaseActor>> skill;
	UPROPERTY()
		FCharacterStat stat;

public:
	void SetTarget(TSubclassOf<class AMonsterCharacter> value) { target = value; }
	void SetWeapon(TSubclassOf<class AItemActor> value) { weapon = value; }
	void SetArmor(TSubclassOf<class AItemActor> value) { armor = value; }
	void SetTool(TSubclassOf<class AItemActor> value) { tool = value; }
	void SetSkill(TSubclassOf<class ASkillBaseActor> value) { skill.Add(value); }
	void SetStat(FCharacterStat value);

	TSubclassOf<class AMonsterCharacter> GetTarget() { return target; }
	TArray<FTransform> GetTargetPoint() { return targetPoint; }
	TSubclassOf<class AItemActor> GetWeapon() { return weapon; }
	TSubclassOf<class AItemActor> GetArmor() { return armor; }
	TSubclassOf<class AItemActor> GetTool() { return tool; }
	TArray<TSubclassOf<class ASkillBaseActor>> GetSkill() { return skill; }
	FCharacterStat Getstat() { return stat; }
};
