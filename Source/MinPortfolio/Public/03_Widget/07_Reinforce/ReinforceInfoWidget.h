// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class AItemActor* equipmentItem;
	UPROPERTY()
		class AItemActor* materialItem;

	//equipment
	UPROPERTY()
		class UTextBlock* TextBlock_EquipmentStat;
	UPROPERTY()
		class UTextBlock* TextBlock_EquipmentAddOption;
	UPROPERTY()
		class UImage* Image_Equipment;

	//material
	UPROPERTY()
		class UTextBlock* TextBlock_Materia;
	UPROPERTY()
		class UTextBlock* TextBlock_MaterialAddOption;
	UPROPERTY()
		class UImage* Image_Material;

	//reinforce
	UPROPERTY()
		class UTextBlock* TextBlock_ReinforceStat;
	UPROPERTY()
		class UVerticalBox* VerticalBox_Reinforce;
	UPROPERTY()
		class UImage* Image_Reinforce;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UReinforceeAddOptionWidget> addOptionButtonClass;

	UPROPERTY()
		class UReinforceeAddOptionWidget* nowAddOptionButton;

	UPROPERTY()
		class UCanvasPanel* CanvasPanel_addOptionMany;

	UPROPERTY()
		class UButton* Button_Check;

public:

	UPROPERTY()
		TArray<EAddOptionsType_Equipment> useAddOptions_Armor;
	UPROPERTY()
		TArray<EAddOptionsType_Equipment_Weapon> useAddOptions_Weapon;

	void SetInfo(class AItemActor* equipment, class AItemActor* material);

	FString GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option);
	FString GetAddOptionDescription_Material(EAddOptionsType_Material option);
	FString GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option);
	FString GetAddOptionDescription_ReinforceToArmor(EAddOptionsType_Material option);
	FString GetAddOptionDescription_ReinforceToWeapon(EAddOptionsType_Material option);
	EAddOptionsType_Equipment GetAddOptionToArmor(EAddOptionsType_Material option);
	EAddOptionsType_Equipment_Weapon GetAddOptionToWeapon(EAddOptionsType_Material option);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void PressedDownEvent();
	void PressedUpEvent();

	UFUNCTION()
		void PressedCheckButton();

	virtual void NativeConstruct() override;
};
