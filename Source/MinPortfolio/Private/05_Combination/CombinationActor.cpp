// Fill out your copyright notice in the Description page of Project Settings.


#include "05_Combination/CombinationActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ACombinationActor::ACombinationActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = staticMesh;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	boxComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ACombinationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombinationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

