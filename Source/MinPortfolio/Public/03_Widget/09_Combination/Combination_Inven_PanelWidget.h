// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_Inven_PanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_Inven_PanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_Inven;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCombination_List_ButtonWidget> buttonClass;
public:

	void OnInvenList(UUserWidget* superButton);

	class UVerticalBox* GetVerticalBox_Inven() { return VerticalBox_Inven; }

	const FComNeedInfo* needInfo;

	FName needCode;
};
