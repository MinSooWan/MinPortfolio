// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/07_Reinforce/ReinforceButtonWidget.h"

#include "01_Item/00_Equipment/EquipmentActor.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UReinforceButtonWidget::OnPressedEvnet()
{
}

void UReinforceButtonWidget::OnHoveredEvnet()
{
	Image_button->SetBrushFromTexture(hoveredImage);
}

void UReinforceButtonWidget::OnUnhoveredEvent()
{
	if (item->IsA<AEquipmentActor>())
	{
		if (Cast<AEquipmentActor>(item)->GetEquipped() == true)
		{
			Image_button->SetBrushFromTexture(equippedImage);
		}
		else
		{
			Image_button->SetBrushFromTexture(defaultImage);
		}
	}
	else
	{
		Image_button->SetBrushFromTexture(defaultImage);
	}
}

void UReinforceButtonWidget::SetUpButton(AItemActor* value)
{
	item = value;

	if(item)
	{
		Image_Item->SetBrushFromTexture(item->GetItemInfo<FIteminfo>()->item_Image);
		if(item->IsA<AEquipmentActor>())
		{
			if (Cast<AEquipmentActor>(item)->GetEquipped() == true)
			{
				Image_button->SetBrushFromTexture(equippedImage);
			}
			else
			{
				Image_button->SetBrushFromTexture(defaultImage);
			}
		}
		else
		{
			Image_button->SetBrushFromTexture(defaultImage);
		}
	}
}

void UReinforceButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_item->OnPressed.AddDynamic(this, &UReinforceButtonWidget::OnPressedEvnet);
	Button_item->OnHovered.AddDynamic(this, &UReinforceButtonWidget::OnHoveredEvnet);
	Button_item->OnUnhovered.AddDynamic(this, &UReinforceButtonWidget::OnUnhoveredEvent);
	
}
