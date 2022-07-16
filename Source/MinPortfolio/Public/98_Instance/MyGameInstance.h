// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/ItemType.h"
#include "Engine/GameInstance.h"
#include "Engine/TargetPoint.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FAddOptions
{
	GENERATED_BODY()
public:
	FCharacterStat stat;
	TArray<EAddOptionsType_Material> options;
	bool bIsHidden = false;
};

USTRUCT()
struct FMonsterInfo
{
	GENERATED_BODY()
public:

	bool bIsDestroy = false;
	FVector monLoc;
	FCharacterStat stat;
	FRotator monRot;
};

USTRUCT()
struct FHaveItemInfo
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
class MINPORTFOLIO_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		bool bStartGame = false;

	UPROPERTY()
		TSubclassOf<class AMonsterCharacter> target;

	UPROPERTY(EditAnywhere)
		TArray<FTransform> targetPoint;

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

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> loadingWidgetClass;

public:
	UPROPERTY()
		TMap<FVector, FAddOptions> materialActors;
	UPROPERTY()
		FMonsterInfo monInfo;
	UPROPERTY()
		TArray<FHaveItemInfo> haveItems;
	UPROPERTY()
		TMap<FVector, FMonsterInfo> allMonInfo;
	UPROPERTY()
		bool bInBattle = false;

	UPROPERTY()
		FCharacterStat stat;

	void ClearArrays();

	virtual void Init() override;

	//Set Function
	void SetTarget(TSubclassOf<class AMonsterCharacter> value) { target = value; }
	void SetWeapon(TSubclassOf<class AItemActor> value) { weapon = value; }
	void SetArmor(TSubclassOf<class AItemActor> value) { armor = value; }
	void SetPants(TSubclassOf<class AItemActor> value) { shoes = value; }
	void SetTool(TSubclassOf<class AItemActor> value) { tool = value; }
	void SetSkill(TSubclassOf<class ASkillBaseActor> value) { skill.Add(value); }
	void SetInven(TSubclassOf<class AItemActor> value) { inven.Add(value); }
	void SetStat(FCharacterStat value);
	void SetStartGame(bool value) { bStartGame = value; }
	void SetPlayerLocation(FVector value, FRotator rotvalue) { playerLoc = value; playerRot = rotvalue; }
	void SetHaveItem(FHaveItemInfo value) { haveItems.Add(value); }

	//Get Function
	TSubclassOf<class AMonsterCharacter> GetTarget() { return target; }
	TArray<FTransform> GetTargetPoint() { return targetPoint; }
	TSubclassOf<class AItemActor> GetWeapon() { return weapon; }
	TSubclassOf<class AItemActor> GetArmor() { return armor; }
	TSubclassOf<class AItemActor> GetShoes() { return shoes; }
	TSubclassOf<class AItemActor> GetTool() { return tool; }
	TArray<TSubclassOf<class ASkillBaseActor>> GetSkill() { return skill; }
	TArray<TSubclassOf<class AItemActor>> GetInven() { return inven; }
	FCharacterStat Getstat() { return stat; }
	bool GetStartGame() { return bStartGame; }
	FVector GetPlayerLocation() { return playerLoc; }
	FRotator GetPlayerRotation() { return playerRot; }
	TArray<FHaveItemInfo> GetHaveItems() { return haveItems; }

	UFUNCTION()
		void ShowLoadingScreen(const FString& mapName);
};
