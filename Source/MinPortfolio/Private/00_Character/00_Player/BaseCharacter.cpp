// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/BaseCharacter.h"

#include "BrainComponent.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "TimerManager.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/00_Controller/Battle_AIController.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "96_Save/BattleSaveGame.h"
#include "97_Task/MoveToTarget_Battle_Task.h"
#include "98_Instance/MyGameInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
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

void ABaseCharacter::GiveDamage(float Damage)
{
	float value = statComp->GetHP() - (Damage - GetStatusComponent()->GetDEF() * 0.5);
	statComp->SetHP(FMath::Clamp(value, 0.f, statComp->GetMaxHP()));
}

void ABaseCharacter::ActionChange()
{
	
}

void ABaseCharacter::ActionChange(float cool)
{

}

void ABaseCharacter::ActionChange_Able()
{
	bAbleAction = true;
}

void ABaseCharacter::ActionChange_Impossible()
{
	bAbleAction = false;

}

void ABaseCharacter::LoadToLevel()
{
	UGameplayStatics::DoesSaveGameExist("TestSaveSlot", 0);
	auto SaverSubClass = UGameplayStatics::LoadGameFromSlot("TestSaveSlot", 0);
	if (SaverSubClass != nullptr)
	{
		auto player = Cast<APlayerCharacter>(GetController<ABattle_AIController>()->GetBlackboardComponent()->GetValueAsObject("Target"));

		if (player != nullptr) {

			GetGameInstance<UMyGameInstance>()->bInBattle = false;

			UGameplayStatics::OpenLevel(this, FName(Cast<UBattleSaveGame>(SaverSubClass)->levelName));
		}
	}
}

void ABaseCharacter::MonsterDieToRemove()
{
	GetWorld()->GetTimerManager().ClearTimer(AbleAction);
	GetWorld()->GetTimerManager().ClearTimer(ImpossibleAction);
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	GetMesh()->SetCollisionProfileName("NoCollision");
	SetActorHiddenInGame(true);
}
