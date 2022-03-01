// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/MenuWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/01_Inventory/InventoryButtonWidget.h"
#include "03_Widget/01_Inventory/InventoryPanelWidget.h"
#include "03_Widget/01_Inventory/InventoryWidget.h"
#include "03_Widget/02_Skill/SkillButtonWidget.h"
#include "03_Widget/02_Skill/SkillMainWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "03_Widget/02_Skill/SkillTreeWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/04_EquipmentWidget/EquipmentMainWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetInputLibrary.h"

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

	//Click
	Button_Inventory->OnClicked.AddDynamic(this, &UMenuWidget::InventoryClick);
	Button_Skill->OnClicked.AddDynamic(this, &UMenuWidget::SkillClick);
	Button_Equipment->OnClicked.AddDynamic(this, &UMenuWidget::EquipmentClick);
	Button_Quest->OnClicked.AddDynamic(this, &UMenuWidget::QuestClick);

	//Hovered
	Button_Inventory->OnHovered.AddDynamic(this, &UMenuWidget::InventoryHovered);
	Button_Skill->OnHovered.AddDynamic(this, &UMenuWidget::SkillHovered);
	Button_Equipment->OnHovered.AddDynamic(this, &UMenuWidget::EquipmentHovered);
	Button_Quest->OnHovered.AddDynamic(this, &UMenuWidget::QuestHovered);

	//Unhovered
	Button_Inventory->OnUnhovered.AddDynamic(this, &UMenuWidget::InventoryUnhovered);
	Button_Skill->OnUnhovered.AddDynamic(this, &UMenuWidget::SkillUnhovered);
	Button_Equipment->OnUnhovered.AddDynamic(this, &UMenuWidget::EquipmentUnhovered);
	Button_Quest->OnUnhovered.AddDynamic(this, &UMenuWidget::QuestUnhovered);
}


void UMenuWidget::InventoryClick()
{
	TextBlock_MenuName->SetText(FText::FromString(TEXT("Inventory")));
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackgroundBlur_Image()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetInventoryWidget()->OnInventoryWidget();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetInventoryWidget()->SetFocus();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnInven();
}

void UMenuWidget::SkillClick()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetSkillMainWidget()->GetSkillTreeWidget()->GetRootButton()->SetFocus();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnSkillTree();
}

void UMenuWidget::EquipmentClick()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ACustomController>()->GetMainWidget()->GetEquipmentWidget()->OnEquipmentWidget();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnEquipment();
}

void UMenuWidget::QuestClick()
{
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

void UMenuWidget::OnMenuWidget()
{
	previous_button = Button_Quest;
	next_button = Button_Skill;
	now_button = Button_Inventory;
	Button_Equipment->OnUnhovered.Broadcast();
	Button_Quest->OnUnhovered.Broadcast();
	Button_Skill->OnUnhovered.Broadcast();
	SetVisibility(ESlateVisibility::Visible);
	Button_Inventory->OnHovered.Broadcast();
	Button_Inventory->SetFocus();
}

FReply UMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("Gamepad_RightShoulder"))
	{
		pressedNext();
	}
	else if (InKeyEvent.GetKey() == FKey("Gamepad_LeftShoulder"))
	{
		pressedPrevious();
	}
	else if(InKeyEvent.GetKey() == FKey("E"))
	{
		pressedNext();
	}
	else if(InKeyEvent.GetKey() == FKey("Q"))
	{
		pressedPrevious();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffMenu();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->GetBackGroundImage()->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffMenu();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}
