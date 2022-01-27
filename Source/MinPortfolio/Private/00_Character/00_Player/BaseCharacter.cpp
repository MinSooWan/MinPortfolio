// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "TimerManager.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	statComp = CreateDefaultSubobject<UStatusComponent>(TEXT("statusComp"));
	buffComp = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComp"));

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionComp"));
	AIPerceptionStimuliSourceComponent->bAutoRegister = true;

	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Hearing::StaticClass());
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);


}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ABaseCharacter::AddDebuffStateCharacter(EDebuffState buff, const float value, const float cool, EDebuffType type)
{
	auto debuff = NewObject<UDebuffObject>(debuffclass);
	if (debuff != nullptr) {
		debuffs.Add(debuff);
		debuff->SetDebuff(buff, value);
		debuff->AddDebuffState(value, cool, this, type);
	}

}

void ABaseCharacter::RemoveDebuffState(EDebuffState buff, const float value, UDebuffObject* buffObject)
{
	switch (buff)
	{
	case EDebuffState::GIVE_ATC_DOWN:
		GetStatusComponent()->AddATC(value);
		break;
	case EDebuffState::GIVE_DEF_DOWN:
		GetStatusComponent()->AddDEF(value);
		break;
	case EDebuffState::GIVE_SLOW:
		GetStatusComponent()->AddDEX(value);
		break;
	}

	debuffs.Remove(buffObject);
	buffObject->ConditionalBeginDestroy();
}

void ABaseCharacter::RemoveDebuffObejct(UDebuffObject* buffObject)
{
	debuffs.Remove(buffObject);
}

