// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "Combination_Mate_PanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UCombination_Mate_PanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_MateList;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCombination_Mate_ButtonWidget> ButtonClass;

public:
	class UVerticalBox* GetVerticalBox_MateList() { return VerticalBox_MateList; }

	void InitMateList(const FIteminfo* value);
};
