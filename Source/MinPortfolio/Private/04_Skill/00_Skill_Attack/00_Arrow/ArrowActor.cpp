// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/00_Skill_Attack/00_Arrow/ArrowActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AArrowActor::AArrowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("statucComp"));
	RootComponent = staticMesh;

	staticMesh->SetCollisionProfileName("Projectile");
	staticMesh->SetNotifyRigidBodyCollision(true);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("GlowComp"));
	ParticleComp->SetupAttachment(RootComponent);

	ProjectilMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectilMovementComp->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AArrowActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArrowActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorHit.AddUniqueDynamic(this, &AArrowActor::OnActorHitEvent);
}

void AArrowActor::OnActorHitEvent(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if(hitParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, Hit.Location);
	}
	SelfActor->Destroy();
}

// Called every frame
void AArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

