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

	InputComponent->BindAction("Battle_Attack", EInputEvent::IE_Pressed, GetOwner<APlayerCharacter>(), &APlayerCharacter::PressedBattle_Attack);

	InputComponent->BindAxis("MoveForward", GetOwner<APlayerCharacter>(), &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", GetOwner<APlayerCharacter>(), &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", GetOwner<APlayerCharacter>(), &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", GetOwner<APlayerCharacter>(), &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", GetOwner<APlayerCharacter>(), &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", GetOwner<APlayerCharacter>(), &APlayerCharacter::LookUpAtRate);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, GetOwner<APlayerCharacter>(), &APlayerCharacter::Jump);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, GetOwner<APlayerCharacter>(), &ACharacter::StopJumping);
}

void ABattleController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	APlayerCharacter* player = GetPawn<APlayerCharacter>();

	if(player != nullptr)
	{
		UKismetSystemLibrary::PrintString(this, "controller");
		SetupInputComponent();
		player->GetEquipmentComp()->EquipmentCompInit();
		player->GetToolComp()->ToolCompInit();
		/*
		auto tool = GetWorld()->SpawnActor<AToolBaseActor>(GetGameInstance<UMyGameInstance>()->GetTool());
		tool->UseItem(player);
		player->GetToolChildActor()->SetVisibility(false);

		auto weapon = GetWorld()->SpawnActor<AWeaponBaseActor>(GetGameInstance<UMyGameInstance>()->GetWeapon());
		weapon->UseItem(player);
		//UKismetSystemLibrary::PrintString(this, GetGameInstance<UMyGameInstance>()->GetItemCode().ToString());
		player->GetWeaponChildActor()->SetVisibility(true);

		*/
	}

}
