// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "Components/Image.h"
#include "KeyImage.generated.h"

/**
 * 
 */
UCLASS()
class MINPORTFOLIO_API UKeyImage : public UImage
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FKey GamepadButtonName;
	UPROPERTY(EditAnywhere)
		FKey keyBoradButtonName;

	void ButtonInitImage();
	void ButtonInitImage_Pad();
	void ButtonInitImage_KeyBorad();
};