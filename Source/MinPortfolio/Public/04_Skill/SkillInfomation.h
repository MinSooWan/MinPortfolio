// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "SkillInfomation.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	ATTACK,
	EFFECT,
	HEAL,
	PASSIVE
};

UENUM(BlueprintType)
enum class ESkillAddOptions : uint8
{
	GIVE_DAMAGE,
	GIVE_BURN,
	GIVE_FROZEN,
	GIVE_SHOCK,
	GIVE_SLOW,
	GIVE_ATC_DOWN,
	GIVE_DEF_DOWN,
	GIVE_ATC_UP,
	GIVE_DEF_UP,
	GIVE_DEX_UP,
	ADD_MAX
};

USTRUCT(BlueprintType)
struct FSkill : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_icon;

	UPROPERTY(EditAnywhere)
		FName skill_Name = NAME_None;

	UPROPERTY(EditAnywhere)
		int32 needSPPoint = 0;

	UPROPERTY(EditAnywhere)
		int32 needAP = 0;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* useSkillMontage;

	UPROPERTY(EditAnywhere)
		bool bCheckUse = false;

	UPROPERTY(EditAnywhere)
		TArray<FName> needSkills;

	UPROPERTY(EditAnywhere)
		TArray<EWeaponType> needWeapon;

	UPROPERTY(EditAnywhere)
		ESkillType skillType;

	UPROPERTY(EditAnywhere)
		FString skill_description;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ASkillBaseActor> skillActorClass;
};

USTRUCT(BlueprintType)
struct FSkill_Attack : public FSkill
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		float damage;

	FSkill_Attack()
	{
		skillType = ESkillType::ATTACK;
	}
};

USTRUCT(BlueprintType)
struct FSkill_Effect : public FSkill
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<ESkillAddOptions> effectOption;

	FSkill_Effect()
	{
		skillType = ESkillType::EFFECT;
	}
};

USTRUCT(BlueprintType)
struct FSkill_Heal : public FSkill
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		float heal = 0;

	FSkill_Heal()
	{
		skillType = ESkillType::HEAL;
	}
};

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API USkillInfomation : public UObject
{
	GENERATED_BODY()
	
};
