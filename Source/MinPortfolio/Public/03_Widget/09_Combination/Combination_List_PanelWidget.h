// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Combination_List_PanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_List_PanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPObject)
		UObject* WeaponTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = BPObject)
		UObject* ArmorTable;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCombination_List_ButtonWidget> buttonClass;

	UPROPERTY()
		class UVerticalBox* VerticalBox_Combination;

public:
	UFUNCTION()
		void OnAllEquipment();
	UFUNCTION()
		void OnWeapon();
	UFUNCTION()
		void OnArmor();
	UFUNCTION()
		void OnShoes();

	class UVerticalBox* GetVerticalBox_Combination() { return VerticalBox_Combination; }
};
