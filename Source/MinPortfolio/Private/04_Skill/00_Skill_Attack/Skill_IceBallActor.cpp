// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_IceBallActor.h"
#include "00_Character/00_Player/BaseCharacter.h"
#include "04_Skill/SkillInfomation.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void ASkill_IceBallActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorHit.AddUniqueDynamic(this, &ASkill_IceBallActor::OnActorHitEvent);
}

void ASkill_IceBallActor::OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ASkill_IceBallActor>(SelfActor)->GetHitParticle(), Hit.Location,
		FRotator::ZeroRotator);
	SelfActor->Destroy();
}

void ASkill_IceBallActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	if (target != nullptr)
	{
		owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);
		auto skill = GetWorld()->SpawnActor<ASkillBaseActor>(GetSkillInfo<FSkill>()->skillActorClass, owner->GetActorLocation() + owner->GetActorForwardVector() * 10, FRotator::ZeroRotator);
		skill->SetLifeSpan(lifeTiem);
		skill->GetProjectilMovementComp()->MaxSpeed = speed;

		skill->GetProjectilMovementComp()->Velocity = target->GetActorLocation() - owner->GetActorLocation();
	}
}
