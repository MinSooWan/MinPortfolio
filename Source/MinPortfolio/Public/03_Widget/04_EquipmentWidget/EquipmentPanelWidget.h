// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentPanelWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentWidget, class UInventoryComponent*, inventoryComp, FName, equipmentType);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquipmentPanelWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UEquipmentButtonWidget> buttonWidgetClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UEquipmentPartsWidget> horizontalBoxClass;
	UPROPERTY()
		class UVerticalBox* VerticalBox_Equipment;
	UPROPERTY()
		TArray<class UEquipmentButtonWidget*> buttons;

	virtual void NativeConstruct() override;

public:

	UPROPERTY()
		FOnEquipmentWidget OnEquipmentWidget;

	UFUNCTION()
		void OnEquipmentWidgetEvent(class UInventoryComponent* inventoryComp, FName equipmentType);

	void ShowWeapon(class UInventoryComponent* inventoryComp);
	void ShowArmor(class UInventoryComponent* inventoryComp);
	void ShowPants(class UInventoryComponent* inventoryComp);

	TArray<class UEquipmentButtonWidget*> GetButtons() { return buttons; }

	void ClearWidget();
};
