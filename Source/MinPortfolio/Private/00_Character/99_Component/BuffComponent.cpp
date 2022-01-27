// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/BuffComponent.h"

#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"

// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuffComponent::AddBuffState(EBuffState buff, const float value, const float cool)
{
	switch (buff)
	{
	case EBuffState::GIVE_ATC_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->AddATC(value);
		break;
	case EBuffState::GIVE_DEF_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->AddDEF(value);
		break;
	case EBuffState::GIVE_DEX_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->AddDEX(value);
		break;
	case EBuffState::GIVE_HP_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->AddMaxHP(value);
		GetOwner<APlayerCharacter>()->GetStatusComponent()->AddHP(value);
		break;
	}

	buffStates.Emplace(buff);

	FTimerHandle buffHandle;

	FTimerDelegate endTimeDel = FTimerDelegate::CreateUObject(this, &UBuffComponent::RemoveBuffState, buff, value);
	GetWorld()->GetTimerManager().SetTimer(buffHandle, endTimeDel, cool, false);
}

void UBuffComponent::RemoveBuffState(EBuffState buff, const float value)
{
	switch (buff)
	{
	case EBuffState::GIVE_ATC_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->SetATC(GetOwner<APlayerCharacter>()->GetStatusComponent()->GetATC() - value);
		break;
	case EBuffState::GIVE_DEF_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->SetDEF(GetOwner<APlayerCharacter>()->GetStatusComponent()->GetDEF() - value);
		break;
	case EBuffState::GIVE_DEX_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->SetDEX(GetOwner<APlayerCharacter>()->GetStatusComponent()->GetDEX() - value);
		break;
	case EBuffState::GIVE_HP_UP:
		GetOwner<APlayerCharacter>()->GetStatusComponent()->SetMaxHP(GetOwner<APlayerCharacter>()->GetStatusComponent()->GetMaxHP() - value);
		GetOwner<APlayerCharacter>()->GetStatusComponent()->SetHP(GetOwner<APlayerCharacter>()->GetStatusComponent()->GetHP() - value);
		break;
	}

	buffStates.Remove(buff);
}
