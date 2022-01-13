// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Material/MaterialBaseActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/WidgetComponent.h"

AMaterialBaseActor::AMaterialBaseActor()
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	RootComponent = sphereComp;

	materialParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("particleComp"));
	materialParticle->SetupAttachment(RootComponent);
	
	pickUpWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	pickUpWidgetComp->SetupAttachment(RootComponent);
	pickUpWidgetComp->SetVisibility(false);
	
	sphereComp->SetCollisionProfileName(TEXT("Material"));
	pickUpWidgetComp->SetCollisionProfileName(TEXT("NoCollision"));

	materialMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	materialMesh->SetupAttachment(RootComponent);
	materialMesh->SetCollisionProfileName(TEXT("NoCollision"));

}

void AMaterialBaseActor::HiddenMesh()
{
	materialMesh->SetVisibility(false);
}
