// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/08_Talk/NPC_TalkWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/02_NPC/NPCCharacter.h"
#include "03_Widget/MainWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UNPC_TalkWidget::SetNPCInfo()
{
	nowString = GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk[0];
	TextBlock_NpcTalk->SetText(FText::FromString(nowString));
	TextBlock_NpcName->SetText(FText::FromString(GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->GetNpcName()));
}

void UNPC_TalkWidget::SetNextTalkText()
{
	if(GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk.Last() != nowString)
	{
		nowString = GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk[GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk.Find(nowString) + 1];
		TextBlock_NpcTalk->SetText(FText::FromString(nowString));
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffNPCTalk();
	}
}

void UNPC_TalkWidget::SetPreTalkText()
{
	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk[0] != nowString)
	{
		nowString = GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk[GetOwningPlayerPawn<APlayerCharacter>()->GetNpc()->talk.Find(nowString) - 1];
		TextBlock_NpcTalk->SetText(FText::FromString(nowString));
	}
}

void UNPC_TalkWidget::OnNPCTalk()
{
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	SetVisibility(ESlateVisibility::Visible);
	SetFocus();
	SetNPCInfo();
	GetOwningPlayer<ACustomController>()->GetMainWidget()->OnNPCTalk();
}

FReply UNPC_TalkWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		SetNextTalkText();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Right))
	{
		SetPreTalkText();
	}
	else if (InKeyEvent.GetKey() == FKey(EKeys::Tab) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_Special_Right))
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
		GetOwningPlayer<ACustomController>()->GetMainWidget()->OffNPCTalk();
	}

	GetOwningPlayer<ACustomController>()->GetMainWidget()->ChangeKeyImage(UKismetInputLibrary::Key_IsGamepadKey(InKeyEvent.GetKey()));
	return FReply::Handled();
}
