// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/SkillBaseActor.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_Skill/SkillInfomation.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASkillBaseActor::ASkillBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	RootComponent = sphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GlowComp"));
	ParticleComp->SetupAttachment(RootComponent);

	ProjectilMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));

	sphereComp->SetCollisionObjectType(ECC_GameTraceChannel6);
	sphereComp->SetNotifyRigidBodyCollision(true);

	ProjectilMovementComp->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void ASkillBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillBaseActor::UseSkill(ABaseCharacter* target)
{
	
}