// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReinforcePanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforcePanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UReinforceButtonWidget> buttonWidgetClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UReinforcePanelPartsWidget> horizontalBoxClass;
	UPROPERTY()
		class UVerticalBox* Vertical_Reinforce;
	UPROPERTY()
		TArray<class UReinforceButtonWidget*> buttons;

public:
	void OnInventoryEvent();

	void ShowEquipment();
	void ShowMaterial();

	TArray<class UReinforceButtonWidget*> GetButtons() { return buttons; }

	void ClearWidget();

	virtual void NativeConstruct() override;

};
