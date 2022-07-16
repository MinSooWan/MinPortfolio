// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/11_Pause/PauseWidget.h"

#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/MainWidget.h"
#include "96_Save/BattleSaveGame.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Save->OnClicked.AddDynamic(this, &UPauseWidget::OnSaveButton);
	Button_Exit->OnClicked.AddDynamic(this, &UPauseWidget::OnExitButton);
}

FReply UPauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::W) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up) ||
		InKeyEvent.GetKey() == FKey(EKeys::S) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down))
	{
		MoveButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		nowButton->OnClicked.Broadcast();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}

void UPauseWidget::OnExitButton()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UPauseWidget::OnSaveButton()
{
	UGameplayStatics::DoesSaveGameExist("TestSaveSlot", 0);
	auto SaverSubClass = UGameplayStatics::CreateSaveGameObject(UBattleSaveGame::StaticClass());
	if (SaverSubClass != nullptr)
	{
		Cast<UBattleSaveGame>(SaverSubClass)->levelName = UGameplayStatics::GetCurrentLevelName(this);
		UGameplayStatics::SaveGameToSlot(SaverSubClass, "SaveSlot", 1);

	}
}

void UPauseWidget::MoveButton()
{
	if(nowButton == Button_Save)
	{
		nowButton->OnUnhovered.Broadcast();
		nowButton = Button_Exit;
		nowButton->OnHovered.Broadcast();
	}
	else
	{
		nowButton->OnUnhovered.Broadcast();
		nowButton = Button_Save;
		nowButton->OnHovered.Broadcast();
	}
}

void UPauseWidget::OnPauseWidget()
{
	nowButton = Button_Save;
	nowButton->OnHovered.Broadcast();
}
