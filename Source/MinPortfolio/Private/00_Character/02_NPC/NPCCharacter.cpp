// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_NPC/NPCCharacter.h"

#include "01_Item/ItemActor.h"
#include "Components/SphereComponent.h"

ANPCCharacter::ANPCCharacter()
{
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("equipmentComp"));
	sphereComp->SetupAttachment(RootComponent);

	sphereComp->SetSphereRadius(200);
	sphereComp->SetCollisionProfileName("NPC");
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<FShopItemType*> itemList;
	shopItemTable->GetAllRows<FShopItemType>("", itemList);

	for(auto iter : itemList)
	{
		auto spawn = GetWorld()->SpawnActor<AItemActor>(iter->shopItem);

		if(spawn != nullptr)
		{
			FCharacterStat itemStat;
			itemStat.MaxHP = 0;
			itemStat.ATC = 0;
			itemStat.DEX = 0;
			itemStat.DEF = 0;
			itemStat.HP = 0;
			spawn->SetItemStat(itemStat);
			ShopItemList.Add(spawn);
			spawn->SetActorHiddenInGame(true);
		}
	}
}
