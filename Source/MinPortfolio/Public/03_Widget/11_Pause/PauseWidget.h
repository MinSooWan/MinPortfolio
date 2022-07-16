// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UButton* Button_Save;
	UPROPERTY()
		class UButton* Button_Exit;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY()
		class UButton* nowButton;

	void MoveButton();

public:

	void OnPauseWidget();

	UFUNCTION()
		void OnExitButton();
	UFUNCTION()
		void OnSaveButton();
};
