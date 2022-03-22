// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReinforcePanelPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforcePanelPartsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UHorizontalBox* HorizontalBox_Parts;

public:

	class UHorizontalBox* GetHorizontar() { return HorizontalBox_Parts; }
	
};
