// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UseItemCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UUseItemCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		FName item_code = NAME_None;

	UPROPERTY()
		class UButton* Button_Yes;
	UPROPERTY()
		class UButton* Button_No;

public:
	virtual void NativeConstruct() override;

	void UseItemEvent();

	void SetItemCode(FName code) { item_code = code; }
};
