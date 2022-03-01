// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Battle_InvenMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UBattle_InvenMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UBattle_InvenButtonWidget> itemButtonWidget;

	UPROPERTY()
		class UScrollBox* ScrollBox_ItemList;

	UPROPERTY()
		class UBattle_InvenButtonWidget* nowItemButton;
	UPROPERTY()
		class UBattle_InvenButtonWidget* nextItemButton;
	UPROPERTY()
		class UBattle_InvenButtonWidget* preItemButton;
public:

	void OnSkillList();
	void OffSkillList();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void PressedNextButton();
	void PressedPreviousButton();
	void PressedNowButton();
};
