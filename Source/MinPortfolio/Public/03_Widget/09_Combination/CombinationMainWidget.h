// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemActor.h"
#include "Blueprint/UserWidget.h"
#include "CombinationMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombinationMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UCombination_List_PanelWidget* UMG_CombinationPanel;
	UPROPERTY()
		class UCanvasPanel* CanvasPanel_List;

	UPROPERTY()
		class UCombination_Mate_PanelWidget* UMG_Combination_Mate_Panel;
	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Mate;

	UPROPERTY()
		class UCombination_Inven_PanelWidget* UMG_Combination_Inven_Panel;
	UPROPERTY()
		class UCanvasPanel* CanvasPanel_Inven;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultTypeImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredTypeImage;

	UPROPERTY()
		class UButton* Button_All;
	UPROPERTY()
		class UButton* Button_Weapon;
	UPROPERTY()
		class UButton* Button_Armor;
	UPROPERTY()
		class UButton* Button_Shoes;

	UPROPERTY()
		class UCombination_List_ButtonWidget* nowItem;
	UPROPERTY()
		class UButton* nowTypeButton;

	UPROPERTY()
		class UHorizontalBox* HorizontalBox_TypeButtons;

	UPROPERTY()
		class UCombination_Mate_ButtonWidget* nowMateItem;

	UPROPERTY()
		class UCombination_List_ButtonWidget* nowInvenItem;

	UPROPERTY()
		TArray<AItemActor*> applyItemList;
public:

	void OnCombination();

	UFUNCTION()
		void OnAllEquipment();
	UFUNCTION()
		void OnWeapon();
	UFUNCTION()
		void OnArmor();
	UFUNCTION()
		void OnShoes();

	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void ItemTypeRight();
	void ItemTypeLeft();

	void ItemListDown();
	void ItemListUp();

	void MateDown();
	void MateUp();

	void InvenDown();
	void InvenUp();

	//Get
	class UCombination_List_PanelWidget* GetUMG_CombinationPanel() { return UMG_CombinationPanel; }
	class UCanvasPanel* GetCanvasPanel_List() { return CanvasPanel_List; }

	class UCombination_Mate_PanelWidget* GetUMG_Combination_Mate_Panel() { return UMG_Combination_Mate_Panel; }
	class UCanvasPanel* GetCanvasPanel_Mate() { return CanvasPanel_Mate; }

	class UCombination_Inven_PanelWidget* GetUMG_Combination_Inven_Panel() { return UMG_Combination_Inven_Panel; }
	class UCanvasPanel* GetCanvasPanel_Inven() { return CanvasPanel_Inven; }

	TArray<AItemActor*> GetApplyItemList() { return applyItemList; }
};
