// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/01_Inventory/UseItemCheckWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "Components/Button.h"

void UUseItemCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Yes->OnClicked.AddDynamic(this, &UUseItemCheckWidget::UseItemEvent);
}

void UUseItemCheckWidget::UseItemEvent()
{
	UE_LOG(LogTemp, Log, TEXT("UseItem"));
	GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComp()->UseItem(item_code);
}
