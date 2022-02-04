// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
		class APlayerCharacter* player;

	UPROPERTY()
		class AMonsterCharacter* target;

	UPROPERTY(EditAnywhere)
		TArray<FTransform> targetPoint;

	UPROPERTY()
		TSubclassOf<class AItemActor> weapon;
	UPROPERTY()
		TSubclassOf<class AItemActor> armor;
	UPROPERTY()
		TSubclassOf<class AItemActor> tool;


public:
	void SetPlayer(class APlayerCharacter* value) { player = value; }
	void SetTarget(class AMonsterCharacter* value) { target = value; }
	void SetWeapon(TSubclassOf<class AItemActor> value) { weapon = value; }
	void SetArmor(TSubclassOf<class AItemActor> value) { armor = value; }
	void SetTool(TSubclassOf<class AItemActor> value) { tool = value; }

	class APlayerCharacter* GetPlayer() { return player; }
	class AMonsterCharacter* GetTarget() { return target; }
	TArray<FTransform> GetTargetPoint() { return targetPoint; }
	TSubclassOf<class AItemActor> GetWeapon() { return weapon; }
	TSubclassOf<class AItemActor> GetArmor() { return armor; }
	TSubclassOf<class AItemActor> GetTool() { return tool; }
};
