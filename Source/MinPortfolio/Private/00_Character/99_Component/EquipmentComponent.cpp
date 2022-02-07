// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/ItemType.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "Kismet/KismetSystemLibrary.h"

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
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::EquipmentCompInit()
{
	
	AItemActor* spawnWeapon = GetWorld()->SpawnActor<AItemActor>(defaultWeaponActorClass);
	AItemActor* spawnArmor = GetWorld()->SpawnActor<AItemActor>(defaultArmorActorClass);
	AItemActor* spawnDouble = GetWorld()->SpawnActor<AItemActor>(defaultDoubleSwordActorClass);
	GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->SetChildActorClass(defaultDoubleSwordActorClass);
	Cast<AEquipmentActor>(GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->GetChildActor())->
		GetStaticMesh()->SetStaticMesh(spawnDouble->GetItemInfo<FWeapon>()->mesh);

	if (spawnWeapon != nullptr && spawnArmor != nullptr) {
		defaultWeaponActor = spawnWeapon;
		defaultArmorActor = spawnArmor;
		defaultDoubleSwordActor = Cast<AEquipmentActor>(GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->GetChildActor());

		weaponActor = defaultWeaponActor;
		armorActor = defaultArmorActor;

		if (weaponActor != nullptr) {
			weaponActor->SetEquipped(true);
		}

		if (armorActor != nullptr) {
			armorActor->SetEquipped(true);
		}

		if(defaultDoubleSwordActor != nullptr)
		{
			
		}

		spawnWeapon->SetActorHiddenInGame(true);
		spawnArmor->SetActorHiddenInGame(true);
	}
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
		item->SetEquipped(true);
		armorActor = item;
	}
}

