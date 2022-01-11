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
	ONE_HAND, BOW, TWO_HAND, WAND, NO_WEAPON
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	TOP, PANTS
};

UENUM(BlueprintType)
enum class EGatheringToolType : uint8
{
	AXE, HOE, PICKAXE, NO_TOOL
};

//��ῡ �ٴ� �߰��ɼ�
UENUM(BlueprintType)
enum class EAddOptionsType_Material : uint8
{
	ADD_ATC, //���ݷ��� ������Ų��.
	ADD_DEF, //������ ������Ų��.
	ADD_DEX, //��ø���� ������Ų��.
	ADD_HP, //�ִ� ü���� ������Ų��.
	ADD_ITEM, //��Ḧ �߰��� ȹ���� �� �ִ�.
	ADD_EXP, //����ġ�� �߰��� ȹ���� �� �ִ�.
	RECOVERY_HP, //���� ü���� ȸ���ȴ�.
	GIVE_DAMAGE, //������ ������� �ش�.
	GIVE_BURN, //������ ȭ���� ������.(�����ð� ���� �ʸ��� �������� �Դ´�.)
	GIVE_FROZEN, //������ ����ȿ���� ������.(�����ð� ���� �ൿ�� �� �Ѵ�.)
	GIVE_SHOCK, //������ ������ ������.(�����ð� ���� �ൿ�� �������� �Դ´�.)
	GIVE_SLOW, //������ ��ȭ�� ������.(�����ð� ���� ��ø���� ���ҵȴ�.)
	GIVE_ATC_DOWN, //������ �����ð� ���� ���ݷ� ����ȿ���� �ش�.
	GIVE_DEF_DOWN, //������ �����ð� ���� ���� ����ȿ���� �ش�.
	ADD_MAX
};

//��� �ٴ� �߰��ɼ�
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

//�����Ҹ�ǰ�� �ٴ� �߰��ɼ�
UENUM(BlueprintType)
enum class EAddOptionsType_BattleItem : uint8
{
	RECOVERY_HP,
	GIVE_DAMAGE,
	GIVE_BURN,
	GIVE_FROZEN,
	GIVE_SHOCK,
	GIVE_SLOW,
	GIVE_ATC_DOWN,
	GIVE_DEF_DOWN,
	ADD_MAX
};

//�����Ҹ�ǰ�� �ٴ� �߰��ɼ�(ȸ��)
UENUM(BlueprintType)
enum class EAddOptionsType_RecoveryItem : uint8
{
	RECOVERY_HP,
	ADD_ATC_TIME, //���ݷ��� �����ð� ���� ������Ų��.
	ADD_DEF_TIME, //������ �����ð� ����������Ų��.
	ADD_DEX_TIME, //��ø���� �����ð� ����������Ų��.
	ADD_HP_TIME, //�ִ� ü���� �����ð� ����������Ų��.(���� ü�µ� ����)
	ADD_MAX
};

USTRUCT(BlueprintType)
struct FIteminfo : public FTableRowBase
{
	GENERATED_BODY()
public:

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

public:
	EItemType GetItemType() { return item_Type; }
	TSubclassOf<class AItemActor> GetItemClass() { return itemActorClass; }
};

//���
USTRUCT(BlueprintType)
struct FItemMaterial : public FIteminfo
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		EMateriarType materiar_Type;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* mesh;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* useParticle;

	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_Material> addOption;	

public:

	FItemMaterial() {
		item_Type = EItemType::MATERIAL;
	}

	TArray<EAddOptionsType_Material> GetAddOption() { return addOption; }
	EMateriarType GetMateriarType() { return materiar_Type; }
	
};

//���
USTRUCT(BlueprintType)
struct FEquipment : public FIteminfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_Equipment> addOption;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* mesh;
	UPROPERTY(EditAnywhere)
		EEquipmentType equipment_Type;
	UPROPERTY(EditAnywhere)
		FCharacterStat equipmentStat;

public:
	FEquipment() {
		item_Type = EItemType::EQUIPMENT;
	}

	TArray<EAddOptionsType_Equipment> GetAddOption() { return addOption; }
	EEquipmentType GetEquipmentType() { return equipment_Type; }
	FCharacterStat GetEquipmentStat() { return equipmentStat; }
};

//����
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
		EWeaponType weaponType;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* AttackParticle;

public:
	FWeapon() {
		equipment_Type = EEquipmentType::WEAPON;
	}

	EWeaponType GetWeaponType() { return weaponType; }
	class UAnimMontage* GetAttackMontage() { return attackMontage; }
	class UAnimMontage* GetRollMontage() { return rollMontage; }
};

//��
USTRUCT(BlueprintType)
struct FArmor : public FEquipment
{
	GENERATED_BODY()

public:
	EArmorType armorType;	

public:
	FArmor() {
		equipment_Type = EEquipmentType::ARMOR;
	}

	EArmorType GetArmorType() { return armorType; }
};

//�Ҹ�ǰ
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
public:
	FBattleItem() {
		item_Type = EItemType::BATTLE_ITEM;
	}

	EBattleItemType GetBattleItemType() { return battleItemType; }
	class UAnimMontage* GetUseItemAnim() { return useItemAnim; }
	bool GetItemUsedCheck() { return bItemUsed; }
	void SetItemUsed(bool use) { bItemUsed = use; }
};

//������ �Ҹ�ǰ
USTRUCT(BlueprintType)
struct FBattle_Consume : public FBattleItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_BattleItem> addOption;	
	
public:
	FBattle_Consume() {
		battleItemType = EBattleItemType::BATTLE_CONSUME;
	}

	UPROPERTY(EditAnywhere)
		float damage;

	TArray<EAddOptionsType_BattleItem> GetAddOption() { return addOption; }
};

//ȸ�� �Ҹ�ǰ
USTRUCT(BlueprintType)
struct FRecovery_Consume : public FBattleItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<EAddOptionsType_RecoveryItem> addOption;
	
	FRecovery_Consume() {
		battleItemType = EBattleItemType::RECOVERY_CONSUME;
	}

	UPROPERTY(EditAnywhere)
		float recover;

	TArray<EAddOptionsType_RecoveryItem> GetAddOption() { return addOption; }
};

//EGatheringToolType
//ä������
USTRUCT(BlueprintType)
struct FGatheringTool : public FIteminfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* useToolAnim;

	UPROPERTY(EditAnywhere)
		EGatheringToolType toolType;

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
