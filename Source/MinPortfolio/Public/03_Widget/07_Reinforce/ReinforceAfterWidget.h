// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/ItemType.h"
#include "Blueprint/UserWidget.h"
#include "ReinforceAfterWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UReinforceAfterWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UImage* Image_item;
	UPROPERTY()
		class UTextBlock* TextBlock_Stat;
	UPROPERTY()
		class UTextBlock* TextBlock_AddOption;

public:
	void InitInfo(class AItemActor* item);

	FString GetAddOptionDescription_Equipment(EAddOptionsType_Equipment option);
	FString GetAddOptionDescription_WeaponItem(EAddOptionsType_Equipment_Weapon option);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
};
