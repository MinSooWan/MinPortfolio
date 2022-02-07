// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/BattleController.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "98_Instance/MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void ABattleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Battle_Attack", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PressedBattle_Attack);

	InputComponent->BindAction("Battle_Skill", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::TempUseSkill);
}

void ABattleController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	APlayerCharacter* player = GetPawn<APlayerCharacter>();

	if(player != nullptr)
	{
		SetupInputComponent();
		player->GetEquipmentComp()->EquipmentCompInit();
		player->GetToolComp()->ToolCompInit();
		
	}

}
