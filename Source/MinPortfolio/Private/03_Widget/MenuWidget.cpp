// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/MenuWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	buttonArray.Emplace(Button_Inventory);
	buttonArray.Emplace(Button_Skill);
	buttonArray.Emplace(Button_Equipment);
	buttonArray.Emplace(Button_Quest);

	previous_button = Button_Quest;
	next_button = Button_Skill;
	now_button = Button_Inventory;

	//Pressed
	Button_Inventory->OnPressed.AddDynamic(this, &UMenuWidget::InventoryPressed);
	Button_Skill->OnPressed.AddDynamic(this, &UMenuWidget::SkillPressed);
	Button_Equipment->OnPressed.AddDynamic(this, &UMenuWidget::EquipmentPressed);
	Button_Quest->OnPressed.AddDynamic(this, &UMenuWidget::QuestPressed);

	//Hovered
	Button_Inventory->OnHovered.AddDynamic(this, &UMenuWidget::UMenuWidget::InventoryHovered);
	Button_Skill->OnHovered.AddDynamic(this, &UMenuWidget::UMenuWidget::SkillHovered);
	Button_Equipment->OnHovered.AddDynamic(this, &UMenuWidget::UMenuWidget::EquipmentHovered);
	Button_Quest->OnHovered.AddDynamic(this, &UMenuWidget::UMenuWidget::QuestHovered);

	//Unhovered
	Button_Inventory->OnUnhovered.AddDynamic(this, &UMenuWidget::UMenuWidget::UMenuWidget::InventoryUnhovered);
	Button_Skill->OnUnhovered.AddDynamic(this, &UMenuWidget::UMenuWidget::SkillUnhovered);
	Button_Equipment->OnUnhovered.AddDynamic(this, &UMenuWidget::UMenuWidget::EquipmentUnhovered);
	Button_Quest->OnUnhovered.AddDynamic(this, &UMenuWidget::UMenuWidget::QuestUnhovered);
}

//Pressed
void UMenuWidget::InventoryPressed()
{
	SetImage(Image_Inventory, pressedImage);
}

void UMenuWidget::SkillPressed()
{
	SetImage(Image_Skill, pressedImage);
}

void UMenuWidget::EquipmentPressed()
{
	SetImage(Image_Equipment, pressedImage);
}

void UMenuWidget::QuestPressed()
{
	SetImage(Image_Quest, pressedImage);
}

//Hovered
void UMenuWidget::InventoryHovered()
{
	SetImage(Image_Inventory, pressedImage);
}

void UMenuWidget::SkillHovered()
{
	SetImage(Image_Skill, pressedImage);
}

void UMenuWidget::EquipmentHovered()
{
	SetImage(Image_Equipment, pressedImage);
}

void UMenuWidget::QuestHovered()
{
	SetImage(Image_Quest, pressedImage);
}

//Unhovered
void UMenuWidget::InventoryUnhovered()
{
	SetImage(Image_Inventory, defaultImage);
}

void UMenuWidget::SkillUnhovered()
{
	SetImage(Image_Skill, defaultImage);
}

void UMenuWidget::EquipmentUnhovered()
{
	SetImage(Image_Equipment, defaultImage);
}

void UMenuWidget::QuestUnhovered()
{
	SetImage(Image_Quest, defaultImage);
}

void UMenuWidget::SetImage(UImage* widget_image, UTexture2D* image)
{
	widget_image->SetBrushFromTexture(image);
}

void UMenuWidget::pressedNext()
{
	now_button->OnUnhovered.Broadcast();
	previous_button = now_button;
	now_button = next_button;

	for (int i = 0; i < buttonArray.Num(); i++)
	{
		auto iter = buttonArray[i];

		if (iter == now_button)
		{
			if (i == buttonArray.Num() - 1)
			{
				next_button = buttonArray[0];
			}
			else
			{
				next_button = buttonArray[i + 1];
			}
			now_button->OnHovered.Broadcast();
			now_button->SetFocus();
			break;
		}
	}
}

void UMenuWidget::pressedPrevious()
{
	now_button->OnUnhovered.Broadcast();
	next_button = now_button;
	now_button = previous_button;

	for(int i = 0; i < buttonArray.Num(); i++)
	{
		auto iter = buttonArray[i];

		if(iter == now_button)
		{
			if(i == 0)
			{
				previous_button = buttonArray[buttonArray.Num() - 1];
			}
			else
			{
				previous_button = buttonArray[i - 1];
			}
			now_button->OnHovered.Broadcast();
			now_button->SetFocus();
			break;
		}
	}
}

FReply UMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Gamepad_RightShoulder"))
	{
		pressedNext();
		return FReply::Handled();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_LeftShoulder"))
	{
		pressedPrevious();
		return FReply::Handled();
	}
	else if(InKeyEvent.GetKey() == FKey("E"))
	{
		pressedNext();
		return FReply::Handled();
	}
	else if(InKeyEvent.GetKey() == FKey("Q"))
	{
		pressedPrevious();
		return FReply::Handled();
	}

	return FReply::Handled();
}
