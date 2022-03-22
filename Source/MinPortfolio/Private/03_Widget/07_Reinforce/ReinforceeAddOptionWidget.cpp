// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceeAddOptionWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UReinforceeAddOptionWidget::SetDefaultImage()
{
	Image_Button->SetBrushFromSoftTexture(defaultImage);
}

void UReinforceeAddOptionWidget::SetHoveredImage()
{
	Image_Button->SetBrushFromSoftTexture(hoveredImage);
}

void UReinforceeAddOptionWidget::SetSelectImage()
{
	Image_Button->SetBrushFromSoftTexture(selectImage);
}

void UReinforceeAddOptionWidget::SetAddOptionText(FString str)
{
	TextBlock_AddOption->SetText(FText::FromString(str));
}
