// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UEquipmentPartsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UHorizontalBox* HorizontalBox_Parts;

public:

	class UHorizontalBox* GetHorizontalBox_Parts() { return HorizontalBox_Parts; }
};
