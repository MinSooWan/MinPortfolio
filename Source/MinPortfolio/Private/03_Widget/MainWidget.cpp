// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/MainWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "03_Widget/EquippedItemWidget.h"
#include "03_Widget/MenuWidget.h"
#include "03_Widget/03_KeyImage/KeyImage.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_TimeAndHP/TimeAndHpWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "03_Widget/11_Pause/PauseWidget.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnMenuWidget.AddDynamic(this, &UMainWidget::OnMenuWidgetEvent);
	ChangeKeyMode.AddDynamic(this, &UMainWidget::ChangeKeyImage);

	UMG_TimeAndHp_Player->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_AP->SetVisibility(ESlateVisibility::Hidden);

	InitKeyImage();

	if(GetOwningPlayer()->IsA<ABattleController>())
	{
		UMG_EquippedItem->SetVisibility(ESlateVisibility::Hidden);
		UMG_TimeAndHp_Player->SetVisibility(ESlateVisibility::Visible);
		CanvasPanel_AP->SetVisibility(ESlateVisibility::Visible);
		InitAPValue();
	}
	else if(GetOwningPlayer()->IsA<ACustomController>())
	{
		
	}
}

void UMainWidget::OnMenuWidgetEvent()
{
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	UMG_MenuWidget->OnMenuWidget();
	UMG_MenuWidget->GetTextBlock_MenuName()->SetText(FText::FromString(TEXT("Menu")));
	Image_BackGround->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);
	OnMenu();
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

void UMainWidget::PresedOnPause()
{
	if (!UMG_Pause->IsVisible()) {
		UMG_Pause->OnPauseWidget();
	}
}

void UMainWidget::OnMenu()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffMenu()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);

	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNextLevel() != nullptr || GetOwningPlayerPawn<APlayerCharacter>()->GetNpc() != nullptr) {
		UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::OnInven()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffInven()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OnSkillTree()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffSkillTree()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OnEquipment()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffEquipment()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OnShop()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffShop()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);

	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNextLevel() != nullptr || GetOwningPlayerPawn<APlayerCharacter>()->GetNpc() != nullptr) {
		UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::OnReinforce()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffReinforce()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);

	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNextLevel() != nullptr || GetOwningPlayerPawn<APlayerCharacter>()->GetNpc() != nullptr) {
		UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::OnNPCTalk()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::OffNPCTalk()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);

	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNextLevel() != nullptr || GetOwningPlayerPawn<APlayerCharacter>()->GetNpc() != nullptr
		|| GetOwningPlayer<APlayerCharacter>()->GetCom() != nullptr) {
		UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::OnCom()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Visible);
}

void UMainWidget::OffCom()
{
	UMG_Key->GetCanvasPanel_Main()->SetVisibility(ESlateVisibility::Visible);
	UMG_Key->GetCanvasPanel_Menu()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Skill()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Inven()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Equipment()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Shop()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforce()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_ReinforceAfter()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Reinforceinfo()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_NPCTalk()->SetVisibility(ESlateVisibility::Hidden);
	UMG_Key->GetCanvasPanel_Com()->SetVisibility(ESlateVisibility::Hidden);

	if (GetOwningPlayerPawn<APlayerCharacter>()->GetNextLevel() != nullptr || GetOwningPlayerPawn<APlayerCharacter>()->GetNpc() != nullptr
		|| GetOwningPlayerPawn<APlayerCharacter>()->GetCom() != nullptr) {

		UMG_Key->GetCanvasPanel_Going()->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainWidget::InitAPValue()
{
	TextBlock_APValue->SetText(FText::FromString(FString::FromInt(GetOwningPlayerPawn<APlayerCharacter>()->GetStatusComponent()->GetActionsPoint())));
}
