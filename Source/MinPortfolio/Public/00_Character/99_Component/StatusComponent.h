// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float HP;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MaxHP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float ATC;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float DEF;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float DEX;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 SkillPoint;

	FCharacterStat& operator+=(const FCharacterStat& Add) {
		this->HP += Add.HP;
		this->MaxHP += Add.MaxHP;
		this->ATC += Add.ATC;
		this->DEF += Add.DEF;
		this->DEX += Add.DEX;
		this->SkillPoint += Add.SkillPoint;
		return *this;
	}

	FCharacterStat& operator+(const FCharacterStat& Add) {
		this->HP += Add.HP;
		this->MaxHP += Add.MaxHP;
		this->ATC += Add.ATC;
		this->DEF += Add.DEF;
		this->DEX += Add.DEX;
		this->SkillPoint += Add.SkillPoint;
		return *this;
	}

	FCharacterStat& operator-=(const FCharacterStat& Add) {
		this->HP -= Add.HP;
		this->MaxHP -= Add.MaxHP;
		this->ATC -= Add.ATC;
		this->DEF -= Add.DEF;
		this->DEX -= Add.DEX;
		this->SkillPoint -= Add.SkillPoint;
		return *this;
	}

	FCharacterStat& operator-(const FCharacterStat& Add) {
		this->HP -= Add.HP;
		this->MaxHP -= Add.MaxHP;
		this->ATC -= Add.ATC;
		this->DEF -= Add.DEF;
		this->DEX -= Add.DEX;
		this->SkillPoint -= Add.SkillPoint;
		return *this;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINPORTFOLIO_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FCharacterStat characterStat;

	class ABaseCharacter* OwnerCharacter;

public:	
	const FCharacterStat& GetCharacterStat() { return characterStat; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init();

	virtual void InitializeComponent() override;

	float GetHP() { return characterStat.HP; }
	float GetMaxHP() { return  characterStat.HP; }
	float GetATC() { return characterStat.ATC; }
	float GetDEF() { return characterStat.DEF; }
	float GetDEX() { return characterStat.DEX; }
	int32 GetSP() { return characterStat.SkillPoint; }

	void AddHP(const float value);
	void AddMaxHP(const float value);
	void AddATC(const float value);
	void AddDEF(const float value);
	void AddDEX(const float value);
	void AddSP(const int32 value);

	void SetHP(const float value);
	void SetMaxHP(const float value);
	void SetATC(const float value);
	void SetDEF(const float value);
	void SetDEX(const float value);
	void SetSP(const int32 value);

	void AddStat(const FCharacterStat& statToAdd);
	void RemoveStat(const FCharacterStat& statToRemove);
};
