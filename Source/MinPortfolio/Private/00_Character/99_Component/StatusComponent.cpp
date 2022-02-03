// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/BaseCharacter.h"

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
}

