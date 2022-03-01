// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenMainWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenButtonWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UBattle_InvenMainWidget::OnSkillList()
{
	auto owner = GetOwningPlayerPawn<APlayerCharacter>();

	if (owner != nullptr)
	{
		ScrollBox_ItemList->ClearChildren();

		SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeUIOnly());
		SetFocus();

		UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);

		UKismetSystemLibrary::PrintString(GetOwningPlayer(), "CreateWidget");
		for (auto iter : owner->GetInventoryComp()->GetItemArray())
		{
			if (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type == EItemType::BATTLE_ITEM) {
				if (Cast<AItemActor>(iter)->GetItemInfo<FBattleItem>()->battleItemType == EBattleItemType::BATTLE_CONSUME) {

					auto itemWidget = CreateWidget<UBattle_InvenButtonWidget>(GetOwningPlayer(), itemButtonWidget);

					itemWidget->InitButton(Cast<AItemActor>(iter));
					ScrollBox_ItemList->AddChild(itemWidget);
				}
			}
		}
		
		auto widgets = ScrollBox_ItemList->GetAllChildren();

		if (widgets.Num() != 0) {
			nowItemButton = Cast<UBattle_InvenButtonWidget>(widgets[0]);

			if (widgets.Num() > 1) {
				nextItemButton = Cast<UBattle_InvenButtonWidget>(widgets[1]);
				preItemButton = Cast<UBattle_InvenButtonWidget>(widgets[widgets.Num() - 1]);
			}

			nowItemButton->OnHoveredEvent();
		}
	}
}

void UBattle_InvenMainWidget::OffSkillList()
{
	ScrollBox_ItemList->ClearChildren();

	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeGameOnly());
	SetUserFocus(GetOwningPlayer());

	UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
}

FReply UBattle_InvenMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey(EKeys::E) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder))
	{
		PressedNextButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Q) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder))
	{
		PressedPreviousButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		PressedNowButton();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Escape) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		OffSkillList();
	}

	GetOwningPlayer<ABattleController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));

	return FReply::Handled();
}

void UBattle_InvenMainWidget::PressedNextButton()
{
	if (ScrollBox_ItemList->GetAllChildren().Num() > 1) {
		nowItemButton->OnUnhoveredEvent();

		preItemButton = nowItemButton;
		nowItemButton = nextItemButton;

		int32 index = ScrollBox_ItemList->GetAllChildren().Find(nowItemButton);
		if (index != ScrollBox_ItemList->GetAllChildren().Find(ScrollBox_ItemList->GetAllChildren().Last()))
		{
			nextItemButton = Cast<UBattle_InvenButtonWidget>(ScrollBox_ItemList->GetAllChildren()[index + 1]);
		}
		else
		{
			nextItemButton = Cast<UBattle_InvenButtonWidget>(ScrollBox_ItemList->GetAllChildren()[0]);
		}

		nowItemButton->OnHoveredEvent();
		nowItemButton->SetFocus();
	}
}

void UBattle_InvenMainWidget::PressedPreviousButton()
{
	if (ScrollBox_ItemList->GetAllChildren().Num() > 1) {
		nowItemButton->OnUnhoveredEvent();

		nextItemButton = nowItemButton;
		nowItemButton = preItemButton;

		int32 index = ScrollBox_ItemList->GetAllChildren().Find(nowItemButton);
		if (index != 0)
		{
			preItemButton = Cast<UBattle_InvenButtonWidget>(ScrollBox_ItemList->GetAllChildren()[index - 1]);
		}
		else
		{
			preItemButton = Cast<UBattle_InvenButtonWidget>(ScrollBox_ItemList->GetAllChildren().Last());
		}

		nowItemButton->OnHoveredEvent();
		nowItemButton->SetFocus();
	}
}

void UBattle_InvenMainWidget::PressedNowButton()
{
	nowItemButton->OnPressedEvent();
}
