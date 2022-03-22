// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "ItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	MATERIAL, EQUIPMENT, GATHERING_TOOL, BATTLE_ITEM
};

UENUM(BlueprintType)
enum class EMateriarType : uint8
{
	PLANT, WOOD, LEATHER, ORE
};

UENUM(BlueprintType)
enum class EBattleItemType : uint8
{
	BATTLE_CONSUME, RECOVERY_CONSUME
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	WEAPON, ARMOR
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	SWORD, BOW, WAND, NO_WEAPON
};

UENUM(BlueprintType)
enum class ESwordType : uint8
{
	ONE_HAND, TWO_HAND, DOUBLE_SWORD
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	TOP, SHOES
};

UENUM(BlueprintType)
enum class EGatheringToolType : uint8
{
	AXE, HOE, PICKAXE, NO_TOOL
};

//재료에 붙는 추가옵션
UENUM(BlueprintType)
enum class EAddOptionsType_Material : uint8
{
	ADD_ATC, //공격력을 증가시킨다.
	ADD_DEF, //방어력을 증가시킨다.
	ADD_DEX, //민첩성을 증가시킨다.
	ADD_HP, //최대 체력을 증가시킨다.
	ADD_ITEM, //재료를 추가로 획득할 수 있다.
	ADD_EXP, //경험치를 추가로 획득할 수 있다.
	RECOVERY_HP, //사용시 추가로 체력이 회복된다.
	GIVE_DAMAGE, //적에게 추가대미지를 준다.
	GIVE_BURN, //적에게 화상을 입힌다.(일정시간 동안 초마다 데미지를 입는다.)
	GIVE_FROZEN, //적에게 동상효과를 입힌다.(일정시간 동안 행동을 못 한다.)
	GIVE_SHOCK, //적에게 감전을 입힌다.(일정시간 동안 행동시 데미지를 입는다.)
	GIVE_SLOW, //적에게 둔화를 입힌다.(일정시간 동안 민첩성이 감소된다.)
	GIVE_ATC_DOWN, //적에게 일정시간 동안 공격력 감소효과를 준다.
	GIVE_DEF_DOWN, //적에게 일정시간 동안 방어력 감소효과를 준다.
	ADD_ATC_TIME, //공격력을 일정시간 동안 증가시킨다.
	ADD_DEF_TIME, //방어력을 일정시간 동안증가시킨다.
	ADD_DEX_TIME, //민첩성을 일정시간 동안증가시킨다.
	ADD_HP_TIME, //최대 체력을 일정시간 동안증가시킨다.(현재 체력도 증가)
	ADD_MAX
};

//장비에 붙는 추가옵션
UENUM(BlueprintType)
enum class EAddOptionsType_Equipment : uint8
{
	ADD_ATC,
	ADD_DEF,
	ADD_DEX,
	ADD_HP,
	ADD_ITEM,
	ADD_EXP,
	ADD_MAX
};

//무기에 붙는 추가옵션
UENUM(BlueprintType)
enum class EAddOptionsType_Equipment_Weapon : uint8
{
	ADD_ATC,
	ADD_DEF,
	ADD_DEX,
	ADD_HP,
	ADD_ITEM,
	ADD_EXP,
	GIVE_DAMAGE,
	GIVE_BURN,
	GIVE_FROZEN,
	GIVE_SHOCK, 
	GIVE_SLOW,
	ADD_MAX
};

//전투소모품에 붙는 추가옵션
UENUM(BlueprintType)
enum class EAddOptionsType_BattleItem : uint8
{
	GIVE_DAMAGE,
	GIVE_BURN,
	GIVE_FROZEN,
	GIVE_SHOCK,
	GIVE_SLOW,
	GIVE_ATC_DOWN,
	GIVE_DEF_DOWN,
	ADD_MAX
};

//전투소모품에 붙는 추가옵션(회복)
UENUM(BlueprintType)
enum class EAddOptionsType_RecoveryItem : uint8
{
	RECOVERY_HP,
	ADD_ATC_TIME, //공격력을 일정시간 동안 증가시킨다.
	ADD_DEF_TIME, //방어력을 일정시간 동안증가시킨다.
	ADD_DEX_TIME, //민첩성을 일정시간 동안증가시킨다.
	ADD_HP_TIME, //최대 체력을 일정시간 동안증가시킨다.(현재 체력도 증가)
	ADD_MAX
};

USTRUCT(BlueprintType)
struct FComNeedInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image_Com;
	UPROPERTY(EditAnywhere)
		FName item_Code_Com;
	UPROPERTY(EditAnywhere)
		FName item_Name_Com;
};

USTRUCT(BlueprintType)
struct FIteminfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FName item_Name;

	UPROPERTY(EditAnywhere)
		FName item_Code;

	UPROPERTY(EditAnywhere, meta = (MultiLine = true))
		FString item_Description;

	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image;

	UPROPERTY(EditAnywhere)
		EItemType item_Type;

	UPROPERTY(EditAnywhere)
		int32 item_Count;

	UPROPERTY(EditAnywhere)
		int32 item_Price;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> itemActorClass;

	UPROPERTY(EditAnywhere)
		TArray<FComNeedInfo> needItems;

public:
	EItemType GetItemType() { return item_Type; }
	TSubclassOf<class AItemActor> GetItemClass() { return itemActorClass; }
};

//재료
USTRUCT(BlueprintType)
struct FItemMaterial : public FIteminfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		EMateriarType materiar_Type;

	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;

	UPROPERTY(EditAnywhere)
		EGatheringToolType needTool;
		
public:

	FItemMaterial() {
		item_Type = EItemType::MATERIAL;
	}

	EMateriarType GetMateriarType() { return materiar_Type; }
	
};

//장비
USTRUCT(BlueprintType)
struct FEquipment : public FIteminfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;
	UPROPERTY(EditAnywhere)
		EEquipmentType equipment_Type;
	UPROPERTY(EditAnywhere)
		UUserWidget* CombinationWidget;

public:
	FEquipment() {
		item_Type = EItemType::EQUIPMENT;
	}
	EEquipmentType GetEquipmentType() { return equipment_Type; }
};

//무기
USTRUCT(BlueprintType)
struct FWeapon : public FEquipment
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* rollMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* dieMontage;

	UPROPERTY(EditAnywhere)
		EWeaponType weaponType;

	UPROPERTY(EditAnywhere)
		bool bIsSword = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsSword"))
		ESwordType swordType;

	UPROPERTY(EditAnywhere)
		float damage;

public:
	FWeapon() {
		equipment_Type = EEquipmentType::WEAPON;
	}

	EWeaponType GetWeaponType() { return weaponType; }
	class UAnimMontage* GetAttackMontage() { return attackMontage; }
	class UAnimMontage* GetRollMontage() { return rollMontage; }
};

//방어구_값옷
USTRUCT(BlueprintType)
struct FArmor : public FEquipment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EArmorType armorType;	

public:
	FArmor() {
		equipment_Type = EEquipmentType::ARMOR;
	}

	EArmorType GetArmorType() { return armorType; }
};

//소모품
USTRUCT(BlueprintType)
struct FBattleItem : public FIteminfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		EBattleItemType battleItemType;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* useItemAnim;	

	UPROPERTY()
		bool bItemUsed = false;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* useParticle;

	UPROPERTY(EditAnywhere)
		float needCP;

public:
	FBattleItem() {
		item_Type = EItemType::BATTLE_ITEM;
	}

	EBattleItemType GetBattleItemType() { return battleItemType; }
	class UAnimMontage* GetUseItemAnim() { return useItemAnim; }
	bool GetItemUsedCheck() { return bItemUsed; }
	void SetItemUsed(bool use) { bItemUsed = use; }
};

//데미지 소모품
USTRUCT(BlueprintType)
struct FBattle_Consume : public FBattleItem
{
	GENERATED_BODY()

public:

public:
	FBattle_Consume() {
		battleItemType = EBattleItemType::BATTLE_CONSUME;
	}

	UPROPERTY(EditAnywhere)
		float damage;

};

//회복 소모품
USTRUCT(BlueprintType)
struct FRecovery_Consume : public FBattleItem
{
	GENERATED_BODY()

public:

	
	FRecovery_Consume() {
		battleItemType = EBattleItemType::RECOVERY_CONSUME;
	}

	UPROPERTY(EditAnywhere)
		float recover;
};

//EGatheringToolType
//채집도구
USTRUCT(BlueprintType)
struct FGatheringTool : public FIteminfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* useToolAnim;

	UPROPERTY(EditAnywhere)
		EGatheringToolType toolType;

	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* rollMontage;

public:
	FGatheringTool() {
		item_Type = EItemType::GATHERING_TOOL;
	}

	EGatheringToolType GetToolType() { return toolType; }
	class UAnimMontage* GetUseToolAnim() { return useToolAnim; }
};
/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UItemType : public UObject
{
	GENERATED_BODY()

};
