// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_FireBallActor.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/SkillInfomation.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void ASkill_FireBallActor::BeginPlay()
{
	Super::BeginPlay();


}

void ASkill_FireBallActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorHit.AddUniqueDynamic(this, &ASkill_FireBallActor::OnActorHitEvent);
}

void ASkill_FireBallActor::OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<AMonsterCharacter>()) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ASkill_FireBallActor>(SelfActor)->GetHitParticle(), Hit.Location,
			FRotator::ZeroRotator);
		if (skillTarget != nullptr) {
			skillTarget->GiveDamage(GetSkillInfo<FSkill_Attack>()->damage + skillOwner->GetStatusComponent()->GetATC());
		}

		auto num = FMath::RandRange(0, 101);
		if (num >= 40) {
			Cast<APlayerCharacter>(skillOwner)->SetMoveToStatrLocation(true);
			skillTarget->AddDebuffStateCharacter(EDebuffState::GIVE_BURN, 5, 4, EDebuffType::DURATION);
		}

		skillOwner->NormalActionState(EActionState::NORMAL);

		SelfActor->Destroy();
	}
}

void ASkill_FireBallActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	if (target != nullptr)
	{
		FTimerDelegate timeDel;
		timeDel.BindUFunction(this, FName("EndAnimFunction"));

		GetWorld()->GetTimerManager().SetTimer(endSkillHandle, timeDel,
			owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage),
			false);

		auto skill = GetWorld()->SpawnActor<ASkillBaseActor>(GetSkillInfo<FSkill>()->skillActorClass, owner ->GetActorLocation() + owner->GetActorForwardVector() * 10, FRotator::ZeroRotator);

		skill->SetSkillCharacter(owner, target);
		skill->SetLifeSpan(lifeTiem);
		skill->GetProjectilMovementComp()->Velocity = target->GetActorLocation() - owner->GetActorLocation();
	}
}

void ASkill_FireBallActor::EndAnimFunction()
{
	Super::EndAnimFunction();

	
}
