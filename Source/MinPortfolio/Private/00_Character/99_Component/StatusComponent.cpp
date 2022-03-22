// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "03_Widget/MainWidget.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter = GetOwner<ABaseCharacter>();
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusComponent::Init()
{
	characterStat.HP = characterStat.MaxHP;
}

void UStatusComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UStatusComponent::AddHP(const float value)
{
	characterStat.HP = FMath::Clamp(characterStat.HP + value, 0.f, characterStat.MaxHP);
}

void UStatusComponent::AddMaxHP(const float value)
{
	characterStat.MaxHP += value;
}

void UStatusComponent::AddATC(const float value)
{
	characterStat.ATC += value;
}

void UStatusComponent::AddDEF(const float value)
{
	characterStat.DEF += value;
}

void UStatusComponent::AddDEX(const float value)
{
	characterStat.DEX += value;
}

void UStatusComponent::AddSP(const int32 value)
{
	characterStat.SkillPoint += value;
}

void UStatusComponent::AddCharacterLevel()
{
	characterStat.ATC += 10;
	characterStat.DEF += 10;
	characterStat.DEX += 10;
	characterStat.HP += 10;
	characterStat.MaxHP += 10;
	characterStat.SkillPoint += 10;
}

void UStatusComponent::AddEXP(int32 value)
{
	characterStat.EXP += value;
}

void UStatusComponent::AddMaxEXP(const int32 value)
{
	characterStat.MaxEXP += value;
}

void UStatusComponent::AddActionsPoint(const int32 value)
{
	if (characterStat.ActionPoint < 20) {
		characterStat.ActionPoint += value;
		Cast<APlayerCharacter>(GetOwner())->GetController<ABattleController>()->GetMainWidget()->InitAPValue();
	}
}

void UStatusComponent::SetHP(const float value)
{
	characterStat.HP = value;
}

void UStatusComponent::SetMaxHP(const float value)
{
	characterStat.MaxHP = value;
}

void UStatusComponent::SetATC(const float value)
{
	characterStat.ATC = value;
}

void UStatusComponent::SetDEF(const float value)
{
	characterStat.DEF = value;
}

void UStatusComponent::SetDEX(const float value)
{
	characterStat.DEX = value;
}

void UStatusComponent::SetSP(const int32 value)
{
	characterStat.SkillPoint = value;
}

void UStatusComponent::SetCharacterLevel(const int32 value)
{
	characterStat.Character_Level = value;
}

void UStatusComponent::SetEXP(const int32 value)
{
	characterStat.EXP = value;
}

void UStatusComponent::SetMaxEXP(const int32 value)
{
	characterStat.MaxEXP = value;
}

void UStatusComponent::SetActionsPoint(const int32 value)
{
	characterStat.ActionPoint = value;
}

void UStatusComponent::AddStat(const FCharacterStat& statToAdd)
{
	characterStat += statToAdd;
}

void UStatusComponent::RemoveStat(const FCharacterStat& statToRemove)
{
	characterStat -= statToRemove;
}

void UStatusComponent::SetAll(ABaseCharacter* target)
{
	characterStat.ATC = target->GetStatusComponent()->GetATC();
	characterStat.DEF = target->GetStatusComponent()->GetDEF();
	characterStat.DEX = target->GetStatusComponent()->GetDEX();
	characterStat.HP = target->GetStatusComponent()->GetHP();
	characterStat.MaxHP = target->GetStatusComponent()->GetMaxHP();
	characterStat.SkillPoint = target->GetStatusComponent()->GetSP();
	characterStat.Character_Level = target->GetStatusComponent()->GetCharacterLevel();
	characterStat.EXP = target->GetStatusComponent()->GetEXP();
	characterStat.MaxEXP = target->GetStatusComponent()->GetMaxEXP();
}

void UStatusComponent::RandomStat()
{
	characterStat.MaxHP = FMath::RandRange(50, 100) + characterStat.Character_Level;
	characterStat.HP = characterStat.MaxHP;
	characterStat.ATC = FMath::RandRange(FMath::Clamp(characterStat.Character_Level - 10,1, characterStat.Character_Level), characterStat.Character_Level) * 10;
	characterStat.DEF = FMath::RandRange(FMath::Clamp(characterStat.Character_Level - 10, 1, characterStat.Character_Level), characterStat.Character_Level) * 10;
	characterStat.DEX = FMath::RandRange(FMath::Clamp(characterStat.Character_Level - 10, 1, characterStat.Character_Level), characterStat.Character_Level) * 10;
}

