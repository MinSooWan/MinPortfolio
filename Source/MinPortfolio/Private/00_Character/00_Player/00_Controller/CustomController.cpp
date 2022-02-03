// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/CustomController.h"

#include "00_Character/00_Player/BattleCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/99_Component/BuffComponent.h"
#include "03_Widget/MainWidget.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/EquipmentComponent.h"
#include "00_Character/99_Component/InventoryComponent.h"
#include "00_Character/99_Component/SkillComponent.h"

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
	}
}

void ACustomController::ChangeBattleCharacter()
{
	
	APlayerCharacter* player = Cast<APlayerCharacter>(GetPawn());
	auto location = GetPawn()->GetActorLocation();
	auto rotator = GetPawn()->GetActorRotation();
	auto newPawn = GetWorld()->SpawnActor<ABattleCharacter>(BattleCharacterClass, location, rotator);

	newPawn->GetToolChildActor()->SetChildActorClass(player->GetToolChildActor()->GetChildActorClass());
	newPawn->GetToolChildActor()->SetVisibility(false);

	newPawn->GetToolComp()->SetToolActor(player->GetToolComp()->GetToolActor());

	newPawn->GetWeaponChildActor()->SetChildActorClass(player->GetWeaponChildActor()->GetChildActorClass());
	newPawn->GetWeaponChildActor()->SetVisibility(true);

	newPawn->GetDoubleSwordChild()->SetChildActorClass(player->GetDoubleSwordChild()->GetChildActorClass());

	newPawn->GetEquipmentComp()->SetWeaponActor(*player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>(), player->GetEquipmentComp()->GetWeaponActor());

	newPawn->GetEquipmentComp()->SetArmorActor(*player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>(), player->GetEquipmentComp()->GetArmorActor());

	newPawn->GetStatusComponent()->SetAll(player);

	newPawn->GetInventoryComp()->SetItemArray(player->GetInventoryComp()->GetItemArray());

	newPawn->GetMesh()->SetAnimInstanceClass(newPawn->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FGatheringTool>()->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
	SetPawn(newPawn);
	mainWidget->SetVisibility(ESlateVisibility::Hidden);
	
}
