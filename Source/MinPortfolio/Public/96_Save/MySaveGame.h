// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/ItemType.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

USTRUCT()
struct FHaveItemInfo_Save
{
	GENERATED_BODY()
public:
	UPROPERTY()
		bool bEquipped = false;

	UPROPERTY()
		bool bInInven = false;

	UPROPERTY()
		FCharacterStat stat;

	UPROPERTY()
		FString typeString;

	UPROPERTY()
		TArray<EAddOptionsType_Equipment_Weapon> weaponAddOption;
	UPROPERTY()
		TArray<EAddOptionsType_Equipment> armorAddOption;
	UPROPERTY()
		TArray<EAddOptionsType_Material> materialAddOptions;
	UPROPERTY()
		TArray<EAddOptionsType_BattleItem> battleItemAddOptions;
	UPROPERTY()
		TArray<EAddOptionsType_RecoveryItem> recoveryItemAddOptions;
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY()
		FString levelName;

	UPROPERTY()
		bool bSaveGame = false;

	UPROPERTY()
		TSubclassOf<class AItemActor> weapon;
	UPROPERTY()
		TSubclassOf<class AItemActor> armor;

	UPROPERTY()
		TSubclassOf<class AItemActor> shoes;

	UPROPERTY()
		TSubclassOf<class AItemActor> tool;
	UPROPERTY()
		TArray<TSubclassOf<class ASkillBaseActor>> skill;
	UPROPERTY()
		TArray<TSubclassOf<class AItemActor>> inven;
	UPROPERTY()
		FVector playerLoc;
	UPROPERTY()
		FRotator playerRot;

	UPROPERTY()
		TArray<FHaveItemInfo_Save> haveItems;

	UPROPERTY()
		FCharacterStat stat;

	UMySaveGame();

	void ClearArray();
};
