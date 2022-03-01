// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/CustomController.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "03_Widget/MainWidget.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/SkillComponent.h"
#include "01_Item/00_Equipment/ArmorBaseActor.h"
#include "01_Item/00_Equipment/ShoesBaseActor.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/01_Material/MaterialBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "01_Item/03_Battle_Item/BattleItemActor.h"
#include "01_Item/03_Battle_Item/RecoveryConsumeActor.h"
#include "04_Skill/SkillBaseActor.h"
#include "96_Save/BattleSaveGame.h"
#include "98_Instance/MyGameInstance.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

void ACustomController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	APlayerCharacter* player = Cast<APlayerCharacter>(aPawn);

	if (player != nullptr) {

		mainWidget = CreateWidget<UMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr) {

			player->GetToolComp()->ToolCompInit();
			player->GetEquipmentComp()->EquipmentCompInit();

			mainWidget->AddToViewport();
		}
		SetupInputComponent();
	}
}

void ACustomController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (GetPawn<APlayerCharacter>() != nullptr) {
		InputComponent->BindAxis("MoveForward", GetPawn<APlayerCharacter>(), &APlayerCharacter::MoveForward);
		InputComponent->BindAxis("MoveRight", GetPawn<APlayerCharacter>(), &APlayerCharacter::MoveRight);

		InputComponent->BindAxis("Turn", GetPawn<APlayerCharacter>(), &APawn::AddControllerYawInput);
		InputComponent->BindAxis("TurnRate", GetPawn<APlayerCharacter>(), &APlayerCharacter::TurnAtRate);
		InputComponent->BindAxis("LookUp", GetPawn<APlayerCharacter>(), &APawn::AddControllerPitchInput);
		InputComponent->BindAxis("LookUpRate", GetPawn<APlayerCharacter>(), &APlayerCharacter::LookUpAtRate);

		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::Jump);
		InputComponent->BindAction("Jump", EInputEvent::IE_Released, GetPawn<APlayerCharacter>(), &ACharacter::StopJumping);

		InputComponent->BindAction("Run", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PresedRunStart);
		InputComponent->BindAction("Run", EInputEvent::IE_Released, GetPawn<APlayerCharacter>(), &APlayerCharacter::PresedRunStop);

		InputComponent->BindAction("Roll", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PresedRoll);

		InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PresedAttack);

		InputComponent->BindAction("OnMenu", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PresedOnMenu);
	}
}

void ACustomController::ChangeBattleLevel()
{
	APlayerCharacter* player = GetPawn<APlayerCharacter>();

	player->GetMesh()->GetAnimInstance()->StopAllMontages(0.1);

	//무기
	GetGameInstance<UMyGameInstance>()->SetWeapon(player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//갑옷
	GetGameInstance<UMyGameInstance>()->SetArmor(player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//신발
	GetGameInstance<UMyGameInstance>()->SetPants(player->GetEquipmentComp()->GetShoesActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//채집 도구
	GetGameInstance<UMyGameInstance>()->SetTool(player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	//스킬
	for(auto iter : player->GetSkillComp()->GetSkills())
	{
		GetGameInstance<UMyGameInstance>()->SetSkill(Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillActorClass);
	}

	//인벤
	for(auto iter : player->GetInventoryComp()->GetItemArray())
	{
		GetGameInstance<UMyGameInstance>()->SetInven(Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->itemActorClass);

		FString str;
		FHaveItemInfo info;
		switch (Cast<AItemActor>(iter)->GetItemInfo<FIteminfo>()->item_Type)
		{
		case EItemType::BATTLE_ITEM:
			if(Cast<AItemActor>(iter)->GetItemInfo<FBattleItem>()->battleItemType == EBattleItemType::BATTLE_CONSUME)
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
			if(Cast<AItemActor>(iter)->GetItemInfo<FEquipment>()->equipment_Type == EEquipmentType::WEAPON)
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

			GetGameInstance<UMyGameInstance>()->haveItems.Add(info);
			break;
		}
	}

	//스탯
	GetGameInstance<UMyGameInstance>()->SetStat(player->GetStatusComponent()->GetCharacterStat());

	//세이브
	UGameplayStatics::DoesSaveGameExist("TestSaveSlot", 0);
	auto SaverSubClass = UGameplayStatics::CreateSaveGameObject(UBattleSaveGame::StaticClass());
	if (SaverSubClass != nullptr)
	{
		Cast<UBattleSaveGame>(SaverSubClass)->levelName = UGameplayStatics::GetCurrentLevelName(this);
		UGameplayStatics::SaveGameToSlot(SaverSubClass, "TestSaveSlot", 0);

		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(this, AMaterialBaseActor::StaticClass(), actors);

		for(auto iter : actors)
		{
			FAddOptions op;
			for(auto i : Cast<AMaterialBaseActor>(iter)->GetAddOption())
			{
				op.options.Add(i);
			}

			if(Cast<AMaterialBaseActor>(iter)->GetSphereComp()->GetCollisionProfileName() == TEXT("NoCollision"))
			{
				op.bIsHidden = true;
			}
			else
			{
				op.bIsHidden = false;
			}

			op.stat = Cast<AMaterialBaseActor>(iter)->GetItemStat();

			GetGameInstance<UMyGameInstance>()->materialActors.Add(iter->GetActorLocation(), op);
		}

		GetGameInstance<UMyGameInstance>()->SetPlayerLocation(GetPawn()->GetActorLocation(), GetPawn()->GetActorRotation());
	}

	UGameplayStatics::OpenLevel(this, "Demonstration");
}
