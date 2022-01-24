// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NeedSpLackWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UNeedSpLackWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UTextBlock* TextBlock_NeedSp;

	UPROPERTY()
		class UButton* Button_Ok;

	UPROPERTY()
		bool bOnSpLackWidget = false;
public:
	class UButton* GetButton_Ok() { return Button_Ok; }

	virtual void NativeConstruct() override;

	void OnNeedSPLack(int32 sp);

	UFUNCTION()
		void OnButton_OkClickEvent();

	bool GetOnSpLackWidget() { return bOnSpLackWidget; }
};
