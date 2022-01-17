// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMenuWidget);

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY()
		class UEquippedItemWidget* UMG_EquippedItem;

	UPROPERTY()
		class UMenuWidget* UMG_MenuWidget;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnMenuWidgetEvent();

public:
	class UMenuWidget* GetMenuWidget() { return UMG_MenuWidget; }
	
	FOnMenuWidget OnMenuWidget;
};
