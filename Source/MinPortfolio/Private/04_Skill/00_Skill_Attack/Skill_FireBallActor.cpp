// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/Skill_FireBallActor.h"
#include "00_Character/00_Player/BaseCharacter.h"
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
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ASkill_FireBallActor>(SelfActor)->GetHitParticle(), Hit.Location,
		FRotator::ZeroRotator);
	SelfActor->Destroy();
}

void ASkill_FireBallActor::UseSkill(ABaseCharacter* target, ABaseCharacter* owner)
{
	Super::UseSkill(target, owner);

	if (target != nullptr)
	{
		owner->PlayAnimMontage(GetSkillInfo<FSkill>()->useSkillMontage);

		auto skill = GetWorld()->SpawnActor<ASkillBaseActor>(GetSkillInfo<FSkill>()->skillActorClass, owner ->GetActorLocation() + owner->GetActorForwardVector() * 10, FRotator::ZeroRotator);
		
		skill->SetLifeSpan(lifeTiem);
		skill->GetProjectilMovementComp()->MaxSpeed = speed;
		skill->GetProjectilMovementComp()->Velocity = target->GetActorLocation() - owner->GetActorLocation();
	}
}
