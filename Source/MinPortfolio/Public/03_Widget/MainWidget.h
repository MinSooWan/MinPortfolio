// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

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

};
