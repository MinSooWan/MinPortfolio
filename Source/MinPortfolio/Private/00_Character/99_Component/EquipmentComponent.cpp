// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/EquipmentComponent.h"
#include "01_Item/ItemActor.h"
#include "01_Item/ItemType.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "01_Item/00_Equipment/EquipmentActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"

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
	AItemActor* spawnPants = GetWorld()->SpawnActor<AItemActor>(defaultShoesActorClass);

	

	if (spawnWeapon != nullptr && spawnArmor != nullptr && spawnPants != nullptr) {
		if (CheckInven(spawnWeapon) && CheckInven(spawnArmor) && CheckInven(spawnPants)) {
			spawnDouble->SetActorHiddenInGame(true);
			spawnArmor->SetActorHiddenInGame(true);
			spawnWeapon->SetActorHiddenInGame(true);
			spawnPants->SetActorHiddenInGame(true);

			GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->SetChildActorClass(defaultDoubleSwordActorClass);
			
			Cast<AEquipmentActor>(GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->GetChildActor())->
				GetStaticMesh()->SetStaticMesh(spawnDouble->GetItemInfo<FWeapon>()->mesh);

			defaultDoubleSwordActor = Cast<AEquipmentActor>(GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->GetChildActor());

			weaponActor = spawnWeapon;
			armorActor = spawnArmor;
			shoesActor = spawnPants;

			if (weaponActor != nullptr) {
				Cast<AEquipmentActor>(spawnWeapon)->SetEquipped(true);
			}

			if (armorActor != nullptr) {
				Cast<AEquipmentActor>(spawnArmor)->SetEquipped(true);
			}

			if (defaultDoubleSwordActor != nullptr)
			{

			}

			if (shoesActor != nullptr)
			{
				Cast<AEquipmentActor>(spawnPants)->SetEquipped(true);
			}
		}
		else
		{
			spawnWeapon->Destroy();
			spawnArmor->Destroy();
			spawnPants->Destroy();
		}
	}

	GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->SetVisibility(false);
	GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->SetHiddenInGame(true);
	GetOwner<APlayerCharacter>()->GetDoubleSwordChild()->GetChildActor()->SetActorHiddenInGame(true);

	GetOwner<APlayerCharacter>()->GetWeaponChildActor()->SetVisibility(false);
	GetOwner<APlayerCharacter>()->GetWeaponChildActor()->SetHiddenInGame(true);
	GetOwner<APlayerCharacter>()->GetWeaponChildActor()->GetChildActor()->SetActorHiddenInGame(true);
}

void UEquipmentComponent::SetWeaponActor(const FIteminfo& itemInfo, AItemActor* item)
{
	if (item != nullptr) {
		Cast<AEquipmentActor>(item)->SetEquipped(true);
		weaponActor = item;
	}
}

void UEquipmentComponent::SetArmorActor(const FIteminfo& itemInfo, AItemActor* item)
{
	if (item != nullptr) {
		Cast<AEquipmentActor>(item)->SetEquipped(true);
		armorActor = item;
	}
}

void UEquipmentComponent::SetShoesActor(const FIteminfo& itemInfo, AItemActor* item)
{
	if(item != nullptr)
	{
		Cast<AEquipmentActor>(item)->SetEquipped(true);
		shoesActor = item;
	}
}

bool UEquipmentComponent::CheckInven(AItemActor* item)
{
	if(GetOwner<APlayerCharacter>()->GetInventoryComp()->GetItemArray().Contains(item))
	{
		return false;
	}

	return true;
}

void UEquipmentComponent::EquipmentItemAddToInven()
{
	GetOwner<APlayerCharacter>()->GetInventoryComp()->AddItem(weaponActor);
	GetOwner<APlayerCharacter>()->GetInventoryComp()->AddItem(armorActor);
	GetOwner<APlayerCharacter>()->GetInventoryComp()->AddItem(shoesActor);
}
