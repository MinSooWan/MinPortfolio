// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/MainWidget.h"
#include "03_Widget/MenuWidget.h"
#include "Components/Button.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnMenuWidget.AddDynamic(this, &UMainWidget::OnMenuWidgetEvent);
}

void UMainWidget::OnMenuWidgetEvent()
{
	UMG_MenuWidget->SetVisibility(ESlateVisibility::Visible);
	UMG_MenuWidget->GetInventoryButton()->OnHovered.Broadcast();
	UMG_MenuWidget->GetInventoryButton()->SetFocus();
}
