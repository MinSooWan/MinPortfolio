// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/03_KeyImage/KeyImage.h"

#include "03_Widget/MainWidget.h"

void UKeyImage::ButtonImage()
{
	auto image = GetOwningPlayer<ACustomController>()->GetMainWidget()->GetKeyImage()[keyButtonName];
	SetBrushFromTexture(image);
}
