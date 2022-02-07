// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/03_KeyImage/KeyImage.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Widget/MainWidget.h"

void UKeyImage::ButtonInitImage()
{
	auto image = GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeyImage()[keyBoradButtonName];
	SetBrushFromTexture(image);
}

void UKeyImage::ButtonInitImage_Pad()
{
	auto image = GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeyImage()[GamepadButtonName];
	SetBrushFromTexture(image);
}

void UKeyImage::ButtonInitImage_KeyBorad()
{
	auto image = GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeyImage()[keyBoradButtonName];
	SetBrushFromTexture(image);
}
