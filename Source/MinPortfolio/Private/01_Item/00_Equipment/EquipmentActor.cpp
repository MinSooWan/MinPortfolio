// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Item/00_Equipment/EquipmentActor.h"
#include "00_Character/99_Component/StatusComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemType.h"
#include "01_Item/ItemActor.h"
#include "Components/ChildActorComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"

void AEquipmentActor::UseItem(class ABaseCharacter* target)
{
	Super::UseItem(target);
}

void AEquipmentActor::AddStat(ABaseCharacter* target, const FCharacterStat& statToAdd)
{
	target->GetStatusComponent()->AddStat(statToAdd);
}

void AEquipmentActor::RemoveStat(ABaseCharacter* target, const FCharacterStat& statToRemove)
{
	target->GetStatusComponent()->RemoveStat(statToRemove);
}

void AEquipmentActor::ItemChange(APlayerCharacter* player, const FWeapon* info, AItemActor* item)
{
	
}

void AEquipmentActor::ItemChange_Default(APlayerCharacter* player, const FWeapon* info, AItemActor* item)
{
	
}

AEquipmentActor::AEquipmentActor()
{
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));

	RootComponent = staticMesh;

	staticMesh->SetGenerateOverlapEvents(true);
	staticMesh->SetCollisionProfileName("NoCollision");
}
