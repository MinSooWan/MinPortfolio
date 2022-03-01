// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillMainWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/BattleController.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillButtonWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "Components/CanvasPanel.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"

void UBattle_SkillMainWidget::OnSkillList()
{
	auto owner = GetOwningPlayerPawn<APlayerCharacter>();

	if (owner != nullptr)
	{
		ScrollBox_SkillList->ClearChildren();

		SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeUIOnly());
		SetFocus();

		UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);

		for (auto iter : owner->GetSkillComp()->GetSkills())
		{
			if (Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillType != ESkillType::PASSIVE) {
				if (Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillType == ESkillType::EFFECT) {
					auto skillWidget = CreateWidget<UBattle_SkillButtonWidget>(GetOwningPlayer(), skillButtonWidget);

					skillWidget->InitButton(Cast<ASkillBaseActor>(iter));
					ScrollBox_SkillList->AddChild(skillWidget);
				}
				else
				{
					if(Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->needWeapon ==
						Cast<AWeaponBaseActor>(owner->GetEquipmentComp()->GetWeaponActor())->GetItemInfo<FWeapon>()->weaponType)
					{
						auto skillWidget = CreateWidget<UBattle_SkillButtonWidget>(GetOwningPlayer(), skillButtonWidget);

						skillWidget->InitButton(Cast<ASkillBaseActor>(iter));
						ScrollBox_SkillList->AddChild(skillWidget);
					}
				}
			}
		}

		auto widgets = ScrollBox_SkillList->GetAllChildren();

		if (widgets.Num() != 0) {
			nowSkillButton = Cast<UBattle_SkillButtonWidget>(widgets[0]);

			if (widgets.Num() > 1) {
				nextSkillButton = Cast<UBattle_SkillButtonWidget>(widgets[1]);
				preSkillButton = Cast<UBattle_SkillButtonWidget>(widgets[widgets.Num() - 1]);
			}

			nowSkillButton->OnHoveredEvent();
		}
	}
}

void UBattle_SkillMainWidget::OffSkillList()
{
	SetVisibility(ESlateVisibility::Hidden);
	GetOwningPlayer<ABattleController>()->GetMainWidget()->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ABattleController>()->SetInputMode(FInputModeGameOnly());
	SetUserFocus(GetOwningPlayer());

	UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
}

FReply UBattle_SkillMainWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == FKey(EKeys::E) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_RightShoulder))
	{
		PressedNextButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Q) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_LeftShoulder))
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

void UBattle_SkillMainWidget::PressedNextButton()
{
	if (ScrollBox_SkillList->GetAllChildren().Num() > 1) {
		nowSkillButton->OnUnhoveredEvent();

		preSkillButton = nowSkillButton;
		nowSkillButton = nextSkillButton;

		int32 index = ScrollBox_SkillList->GetAllChildren().Find(nowSkillButton);
		if (index != ScrollBox_SkillList->GetAllChildren().Find(ScrollBox_SkillList->GetAllChildren().Last()))
		{
			nextSkillButton = Cast<UBattle_SkillButtonWidget>(ScrollBox_SkillList->GetAllChildren()[index + 1]);
		}
		else
		{
			nextSkillButton = Cast<UBattle_SkillButtonWidget>(ScrollBox_SkillList->GetAllChildren()[0]);
		}

		nowSkillButton->OnHoveredEvent();
		nowSkillButton->SetFocus();
	}
}

void UBattle_SkillMainWidget::PressedPreviousButton()
{
	if (ScrollBox_SkillList->GetAllChildren().Num() > 1) {
		nowSkillButton->OnUnhoveredEvent();

		nextSkillButton = nowSkillButton;
		nowSkillButton = preSkillButton;

		int32 index = ScrollBox_SkillList->GetAllChildren().Find(nowSkillButton);
		if (index != 0)
		{
			preSkillButton = Cast<UBattle_SkillButtonWidget>(ScrollBox_SkillList->GetAllChildren()[index - 1]);
		}
		else
		{
			preSkillButton = Cast<UBattle_SkillButtonWidget>(ScrollBox_SkillList->GetAllChildren().Last());
		}

		nowSkillButton->OnHoveredEvent();
		nowSkillButton->SetFocus();
	}
}

void UBattle_SkillMainWidget::PressedNowButton()
{
	nowSkillButton->OnPressedEvent();
}
