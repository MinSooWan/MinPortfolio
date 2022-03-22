// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/01_Material/MaterialBaseActor.h"

#include "98_Instance/MyGameInstance.h"
#include "99_GameMode/SaveState.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMaterialBaseActor::BeginPlay()
{
	Super::BeginPlay();

	if(GetGameInstance<UMyGameInstance>()->materialActors.Num() > 0)
	{
		for(auto iter: GetGameInstance<UMyGameInstance>()->materialActors)
		{
			if(GetActorLocation() == iter.Key)
			{
				if (iter.Value.bIsHidden == false) {
					for (auto i : iter.Value.options)
					{
						AddOption(i);
					}
					itemStat = iter.Value.stat;
				}
				else
				{
					SetActorHiddenInGame(true);
				}
				break;
			}
		}
	}
	else {
		RandomAddOption();
	}
}

void AMaterialBaseActor::AddOption(EAddOptionsType_Material option)
{
	addOption.Add(option);
}

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

void AMaterialBaseActor::RandomAddOption()
{
	int32 cnt = FMath::RandRange(0, 3);

	for (auto i = 0; i < cnt; i++)
	{
		auto option = EAddOptionsType_Material(rand() % 17);
		AddOption(option);
	}
	itemStat.HP += FMath::RandRange(0, 20);
	itemStat.ATC += FMath::RandRange(0, 20);
	itemStat.DEF += FMath::RandRange(0, 20);
	itemStat.DEX += FMath::RandRange(0, 20);
	itemStat.MaxHP = itemStat.HP;
}
