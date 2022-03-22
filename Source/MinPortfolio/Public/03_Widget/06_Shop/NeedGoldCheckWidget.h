// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NeedGoldCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UNeedGoldCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UButton* Button_Yes;

public:
	class UButton* GetButton_Yes() { return Button_Yes; }

	virtual void NativeConstruct() override;

	UFUNCTION()
		void YesButtonPressedEvnet();
};
