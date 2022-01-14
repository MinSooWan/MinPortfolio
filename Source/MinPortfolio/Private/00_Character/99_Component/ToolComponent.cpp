// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"

// Sets default values for this component's properties
UToolComponent::UToolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UToolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	
}


// Called every frame
void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UToolComponent::SetToolActor(AItemActor* item)
{
	if (item != nullptr) {
		toolActor = item;
	}
}

void UToolComponent::ToolCompInit()
{
	auto toolItem = GetWorld()->SpawnActor<AItemActor>(defaultToolActorClass);

	if (toolItem != nullptr) {
		toolActor = toolItem;

		toolItem->Destroy();
	}
}