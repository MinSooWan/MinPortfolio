// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(AActor* item)
{

	for (auto iter : itemArray) {
		if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Code.IsEqual(Cast<AItemActor>(item)->GetItemInfo<FIteminfo>()->item_Code)) {
			Cast<AItemActor>(iter)->AddItemCount(1);
			item->SetActorHiddenInGame(true);
			//Cast<AItemActor>(item)->HiddenMesh();
			return;
		}
	}	

	itemArray.Emplace(item);
	item->SetActorHiddenInGame(true);
}

void UInventoryComponent::UseItem(FName itemCode)
{
	if (itemCode != "") {
		for (auto item : itemArray) {
			if (Cast<AItemActor>(item)->GetItemInfo<FIteminfo>()->item_Code.IsEqual(itemCode)) {
				Cast<AItemActor>(item)->UseItem(GetOwner<APlayerCharacter>());
				break;
			}
		}
	}
}