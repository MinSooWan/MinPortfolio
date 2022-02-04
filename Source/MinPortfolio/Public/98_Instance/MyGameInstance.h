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
		class AWeaponBaseActor* weapon;
	UPROPERTY()
		class AArmorBaseActor* armor;
	UPROPERTY()
		class AToolBaseActor* tool;


public:
	void SetPlayer(class APlayerCharacter* value) { player = value; }
	void SetTarget(class AMonsterCharacter* value) { target = value; }
	void SetWeapon(class AWeaponBaseActor* value) { weapon = value; }
	void SetArmor(class AArmorBaseActor* value) { armor = value; }
	void SetTool(class AToolBaseActor* value) { tool = value; }

	class APlayerCharacter* GetPlayer() { return player; }
	class AMonsterCharacter* GetTarget() { return target; }
	TArray<FTransform> GetTargetPoint() { return targetPoint; }
	class AWeaponBaseActor* GetWeapon() { return weapon; }
	class AArmorBaseActor* GetArmor() { return armor; }
	class AToolBaseActor* GetTool() { return tool; }
};
