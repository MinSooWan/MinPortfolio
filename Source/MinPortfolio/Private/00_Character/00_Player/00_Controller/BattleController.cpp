// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/BattleController.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "01_Item/03_Battle_Item/BattleItemActor.h"
#include "01_Item/03_Battle_Item/RecoveryConsumeActor.h"
#include "03_Widget/MainWidget.h"
#include "03_Widget/03_KeyImage/KeySettingWidget.h"
#include "03_Widget/05_Battle/UMG_Inven/Battle_InvenMainWidget.h"
#include "03_Widget/05_Battle/UMG_Skill/Battle_SkillMainWidget.h"
#include "04_Skill/SkillBaseActor.h"
#include "04_Skill/SkillInfomation.h"
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

void ABattleController::GoingToHome()
{
	APlayerCharacter* player = GetPawn<APlayerCharacter>();

	player->GetMesh()->GetAnimInstance()->StopAllMontages(0.1);

	GetGameInstance<UMyGameInstance>()->ClearArrays();

	//무기
	GetGameInstance<UMyGameInstance>()->SetWeapon(player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//갑옷
	GetGameInstance<UMyGameInstance>()->SetArmor(player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//신발
	GetGameInstance<UMyGameInstance>()->SetPants(player->GetEquipmentComp()->GetShoesActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//채집 도구
	GetGameInstance<UMyGameInstance>()->SetTool(player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//스킬
	for (auto iter : player->GetSkillComp()->GetSkills())
	{
		GetGameInstance<UMyGameInstance>()->SetSkill(Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillActorClass);
	}

	//인벤
	for (auto iter : player->GetInventoryComp()->GetItemArray())
	{
		GetGameInstance<UMyGameInstance>()->SetInven(Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->itemActorClass);

		FString str;
		FHaveItemInfo info;
		switch (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type)
		{
		case EItemType::BATTLE_ITEM:
			if (Cast<AItemActor>(iter)->GetItemInfo<FBattleItem>()->battleItemType == EBattleItemType::BATTLE_CONSUME)
			{
				str = "BATTLE_CONSUME";
				info.typeString = str;

				for (auto i : Cast<ABattleItemActor>(iter)->GetAddOption()) {
					info.battleItemAddOptions.Add(i);
				}

				GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			}
			else
			{
				str = "RECOVERY_CONSUME";
				info.typeString = str;

				for (auto i : Cast<ARecoveryConsumeActor>(iter)->GetAddOption()) {
					info.recoveryItemAddOptions.Add(i);
				}

				GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			}
			break;
		case EItemType::EQUIPMENT:
			if (Cast<AItemActor>(iter)->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
			{
				str = "WEAPON";
				info.typeString = str;
				info.stat = Cast<AItemActor>(iter)->GetItemStat();

				if (iter == player->GetEquipmentComp()->GetWeaponActor())
				{
					info.bEquipped = true;
				}

				for (auto i : Cast<AWeaponBaseActor>(iter)->GetAddOption()) {
					info.weaponAddOption.Add(i);
				}
				info.stat = Cast<AItemActor>(iter)->GetItemStat();

				GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			}
			else
			{
				for (auto i : Cast<AEquipmentActor>(iter)->GetAddOption()) {
					info.armorAddOption.Add(i);
				}

				if (Cast<AItemActor>(iter)->GetItemInfo<FArmor>()->armorType == EArmorType::TOP) {
					str = "ARMOR";
					if (iter == player->GetEquipmentComp()->GetArmorActor())
					{
						info.bEquipped = true;
					}
				}
				else
				{
					str = "SHOES";
					if (iter == player->GetEquipmentComp()->GetShoesActor())
					{
						info.bEquipped = true;
					}
				}
				info.typeString = str;
				info.stat = Cast<AItemActor>(iter)->GetItemStat();

				GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			}
			break;
		case EItemType::MATERIAL:
			str = "MATERIAL";
			info.typeString = str;

			for (auto i : Cast<AMaterialBaseActor>(iter)->GetAddOption()) {
				info.materialAddOptions.Add(i);
			}
			info.stat = Cast<AItemActor>(iter)->GetItemStat();
			info.bInInven = true;

			GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			break;
		case EItemType::GATHERING_TOOL:

			info.stat = Cast<AItemActor>(iter)->GetItemStat();

			if (iter == player->GetToolComp()->GetToolActor())
			{
				UKismetSystemLibrary::PrintString(this, "Use Tool");
				info.bEquipped = true;
			}

			GetGameInstance<UMyGameInstance>()->haveItems.Add(info);

			break;
		}
	}

	//스탯
	GetGameInstance<UMyGameInstance>()->SetStat(player->GetStatusComponent()->GetCharacterStat());

	//위치 초기화
	GetGameInstance<UMyGameInstance>()->SetPlayerLocation(FVector::ZeroVector, FRotator::ZeroRotator);
}
