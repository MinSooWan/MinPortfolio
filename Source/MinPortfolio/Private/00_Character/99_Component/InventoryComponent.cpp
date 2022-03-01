// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/InventoryComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "98_Instance/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

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

	itemArray.Emplace(item);
	item->SetActorHiddenInGame(true);
}

void UInventoryComponent::UseItem(AActor* item)
{
	if (item != nullptr) {
		for (auto iter : itemArray) {
			if (iter == item) {
				Cast<AItemActor>(iter)->UseItem(GetOwner<APlayerCharacter>());
				break;
			}
		}
	}
}

AActor* UInventoryComponent::FindItem(AActor* item)
{
	if (item != nullptr) {
		for (auto iter : itemArray) {
			if (iter == item) {
				return iter;
			}
		}
	}
	return nullptr;
}