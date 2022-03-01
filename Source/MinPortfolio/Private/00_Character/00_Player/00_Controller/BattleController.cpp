// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/BattleController.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenMainWidget.h"
#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillMainWidget.h"
#include "98_Instance/MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetSystemLibrary.h"

void ABattleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Battle_Attack", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PressedBattle_Attack);

	InputComponent->BindAction("TargetChange_Right", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::targetChange_right);

	InputComponent->BindAction("TargetChange_Left", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::TargetChange_Left);

	InputComponent->BindAction("Battle_Skill", EInputEvent::IE_Pressed, this, &ABattleController::OnPreesedSkillList);

	InputComponent->BindAction("Battle_Inven", EInputEvent::IE_Pressed, this, &ABattleController::OnPreesedInvenList);
}

void ABattleController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	APlayerCharacter* player = Cast<APlayerCharacter>(aPawn);

	if (player != nullptr) {

		mainWidget = CreateWidget<UMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr) {

			mainWidget->AddToViewport();
		}
		SetupInputComponent();
	}
}

void ABattleController::OnPreesedSkillList()
{
	if (GetPawn<APlayerCharacter>()->GetAbleAction() == true && Cast<AMonsterCharacter>(GetPawn<APlayerCharacter>()->target)->GetBattleState() == EActionState::NORMAL) {
		if (GetPawn<APlayerCharacter>()->GetActionState() == EActionState::NORMAL && mainWidget->GetUMG_BattleSkillMain()->IsVisible() == false) {
			mainWidget->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Hidden);
			mainWidget->GetUMG_BattleSkillMain()->OnSkillList();
		}
	}
}

void ABattleController::OnPreesedInvenList()
{
	if (GetPawn<APlayerCharacter>()->GetAbleAction() == true && Cast<AMonsterCharacter>(GetPawn<APlayerCharacter>()->target)->GetBattleState() == EActionState::NORMAL) {
		if (GetPawn<APlayerCharacter>()->GetActionState() == EActionState::NORMAL && mainWidget->GetUMG_BattleInvenMain()->IsVisible() == false) {
			mainWidget->GetKeySetting()->GetCanvasPanel_Battle()->SetVisibility(ESlateVisibility::Hidden);
			mainWidget->GetUMG_BattleInvenMain()->OnSkillList();
		}
	}
}
