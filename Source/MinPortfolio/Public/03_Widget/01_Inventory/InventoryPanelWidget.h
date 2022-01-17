// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanelWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventory, class UInventoryComponent*, inventoryComp);
/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UInventoryPanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryButtonWidget> buttonWidgetClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInvnetoryPanelPartsWidget> horizontalBoxClass;
	UPROPERTY()
		class UVerticalBox* Vertical_Inventory;
	UPROPERTY()
		TArray<class UInventoryButtonWidget*> buttons;

	virtual void NativeConstruct() override;

public:
	UPROPERTY()
		FOnInventory OnInventory;

	UFUNCTION()
		void OnInventoryEvent(class UInventoryComponent* inventoryComp);

	void ShowAll(class UInventoryComponent* inventoryComp);
	void ShowEquipment(class UInventoryComponent* inventoryComp);
	void ShowMaterial(class UInventoryComponent* inventoryComp);
	void ShowTool(class UInventoryComponent* inventoryComp);
	void ShowBattleItem(class UInventoryComponent* inventoryComp);

	TArray<class UInventoryButtonWidget*> GetButtons() { return buttons; }

	void ClearWidget();
};

