// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/MainWidget.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/03_KeyImage/KeyImage.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnMenuWidget.AddDynamic(this, &UMainWidget::OnMenuWidgetEvent);
	ChangeKeyMode.AddDynamic(this, &UMainWidget::ChangeKeyImage);

	InitKeyImage();
}

void UMainWidget::OnMenuWidgetEvent()
{
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	UMG_MenuWidget->OnMenuWidget();
	UMG_MenuWidget->GetTextBlock_MenuName()->SetText(FText::FromString(TEXT("Menu")));
	Image_BackGround->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Visible);
}

void UMainWidget::InitKeyImage()
{
	for(auto iter : keyImages_pad)
	{
		iter->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidget::ChangeKeyImage(bool IsKeyMode)
{
	if(IsKeyMode)
	{
		for(auto iter : keyImages_pad)
		{
			iter->SetVisibility(ESlateVisibility::Visible);
		}

		for (auto iter : keyImages_key)
		{
			iter->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		for (auto iter : keyImages_pad)
		{
			iter->SetVisibility(ESlateVisibility::Collapsed);
		}

		for (auto iter : keyImages_key)
		{
			iter->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
