// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Widget/11_Pause/PauseWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "03_Widget/MainWidget.h"
#include "04_Skill/SkillInfomation.h"
#include "96_Save/BattleSaveGame.h"
#include "96_Save/MySaveGame.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "01_Item/ItemType.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "01_Item/03_Battle_Item/BattleItemActor.h"
#include "01_Item/03_Battle_Item/RecoveryConsumeActor.h"
#include "04_Skill/SkillBaseActor.h"
#include "04_Skill/SkillInfomation.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Button_Save->OnClicked.AddDynamic(this, &UPauseWidget::OnSaveButton);
	Button_Exit->OnClicked.AddDynamic(this, &UPauseWidget::OnExitButton);
}

FReply UPauseWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	//UKismetSystemLibrary::PrintString(GetOwningPlayer(), "In key");
	if(InKeyEvent.GetKey() == FKey(EKeys::W) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Up) ||
		InKeyEvent.GetKey() == FKey(EKeys::S) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_DPad_Down))
	{
		MoveButton();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::SpaceBar) || InKeyEvent.GetKey() == FKey(EKeys::Gamepad_FaceButton_Bottom))
	{
		//nowButton->OnClicked.Broadcast();
		Button_Exit->OnClicked.Broadcast();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::F5))
	{
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
		load();
	}
	else if(InKeyEvent.GetKey() == FKey(EKeys::Escape))
	{
		SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetOwningPlayer(), false);
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
	auto SaverSubClass = UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass());
	if (SaverSubClass != nullptr)
	{
		Cast<UMySaveGame>(SaverSubClass)->levelName = UGameplayStatics::GetCurrentLevelName(this);

		APlayerCharacter* player = GetOwningPlayerPawn<APlayerCharacter>();

		Cast<UMySaveGame>(SaverSubClass)->ClearArray();

		//무기
		Cast<UMySaveGame>(SaverSubClass)->weapon = player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->itemActorClass;

		//갑옷
		Cast<UMySaveGame>(SaverSubClass)->armor = player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>()->itemActorClass;

		//신발
		Cast<UMySaveGame>(SaverSubClass)->shoes = player->GetEquipmentComp()->GetShoesActor()->GetItemInfo<FIteminfo>()->itemActorClass;

		//채집 도구
		Cast<UMySaveGame>(SaverSubClass)->tool = player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->itemActorClass;

		//스킬
		for (auto iter : player->GetSkillComp()->GetSkills())
		{
			Cast<UMySaveGame>(SaverSubClass)->skill.Emplace(Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillActorClass);
		}

		//인벤
		for (auto iter : player->GetInventoryComp()->GetItemArray())
		{
			Cast<UMySaveGame>(SaverSubClass)->inven.Emplace(Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->itemActorClass);

			FString str;
			FHaveItemInfo_Save info;
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

					Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);
				}
				else
				{
					str = "RECOVERY_CONSUME";
					info.typeString = str;

					for (auto i : Cast<ARecoveryConsumeActor>(iter)->GetAddOption()) {
						info.recoveryItemAddOptions.Add(i);
					}

					Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);
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

					Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);
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

					Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);
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

				Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);
				break;
			case EItemType::GATHERING_TOOL:

				info.stat = Cast<AItemActor>(iter)->GetItemStat();

				if (iter == player->GetToolComp()->GetToolActor())
				{
					//UKismetSystemLibrary::PrintString(this, "Use Tool");
					info.bEquipped = true;
				}

				Cast<UMySaveGame>(SaverSubClass)->haveItems.Add(info);

				break;
			}
		}

		//스탯
		Cast<UMySaveGame>(SaverSubClass)->stat = player->GetStatusComponent()->GetCharacterStat();

		//위치
		Cast<UMySaveGame>(SaverSubClass)->playerLoc = player->GetActorLocation();
		Cast<UMySaveGame>(SaverSubClass)->playerRot = player->GetActorRotation();

		Cast<UMySaveGame>(SaverSubClass)->bSaveGame = true;

		UGameplayStatics::SaveGameToSlot(SaverSubClass, "SaveSlot", 1);
	}
}

void UPauseWidget::load()
{
	UMySaveGame* loadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (loadGameInstance != nullptr) {
		UGameplayStatics::OpenLevel(GetOwningPlayer(), FName(loadGameInstance->levelName));
	}
}

void UPauseWidget::MoveButton()
{
	/*
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
	*/
}

void UPauseWidget::OnPauseWidget()
{
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer<ACustomController>()->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GetOwningPlayer(), true);
	//nowButton = Button_Save;
	//nowButton->OnHovered.Broadcast();
	SetFocus();
}
