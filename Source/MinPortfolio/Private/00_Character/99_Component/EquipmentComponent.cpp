// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/ItemType.h"
#include "00_Character/00_Player/PlayerCharacter.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AItemActor* temp = GetWorld()->SpawnActor<AItemActor>(defaultWeaponActorClass);
	if (temp != nullptr) {
		defaultWeaponActor = temp;

		weaponActor = defaultWeaponActor;

		if (weaponActor != nullptr) {
			weaponActor->SetEquipped(true);
		}
	}
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::SetWeaponActor(const FIteminfo& itemInfo, AItemActor* item)
{
	if (item != nullptr) {
		item->SetEquipped(true);
		weaponActor = item;
	}
}

void UEquipmentComponent::SetArmorActor(const FIteminfo& itemInfo, AItemActor* item)
{
	if (item != nullptr) {
		armorActor = item;
	}
}

