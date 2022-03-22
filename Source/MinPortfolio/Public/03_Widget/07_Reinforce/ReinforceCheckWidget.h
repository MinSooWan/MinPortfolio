// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceCheckWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class AItemActor* equipmenet;
	UPROPERTY()
		class AItemActor* mateirial;

	UPROPERTY()
		class UButton* Button_Yes;

	UPROPERTY()
		class UButton* Button_No;

	UPROPERTY()
		class UButton* nowButton;

	UPROPERTY(EditAnywhere)
		class UTexture2D* defaultImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* hoveredImage;

public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void InitCheckWidget(class AItemActor* equipment_value, class AItemActor* material_value);

	void ChangeButton();

	UFUNCTION()
		void YesButtonPressedEvent();
	UFUNCTION()
		void NoButtonPressedEvent();
};
