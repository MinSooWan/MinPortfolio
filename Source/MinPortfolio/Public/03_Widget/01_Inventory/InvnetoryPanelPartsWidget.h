// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InvnetoryPanelPartsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UInvnetoryPanelPartsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UHorizontalBox* HorizontalBox_Parts;

public:

	class UHorizontalBox* GetHorizontar() { return HorizontalBox_Parts; }
};
