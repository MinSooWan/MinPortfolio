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
#include "01_Item/00_Weapon/WeaponBaseActor.h"
#include "01_Item/02_Tool/ToolBaseActor.h"
#include "04_Skill/SkillBaseActor.h"
#include "98_Instance/MyGameInstance.h"
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

		InputComponent->BindAction("AnyKey", EInputEvent::IE_Pressed, GetPawn<APlayerCharacter>(), &APlayerCharacter::PressedAnyKey);
	}
}

void ACustomController::ChangeBattleLevel()
{
	APlayerCharacter* player = GetPawn<APlayerCharacter>();

	player->GetMesh()->GetAnimInstance()->StopAllMontages(0.1);

	GetGameInstance<UMyGameInstance>()->SetWeapon(player->GetEquipmentComp()->GetWeaponActor()->GetItemInfo<FIteminfo>()->itemActorClass);
	GetGameInstance<UMyGameInstance>()->SetArmor(player->GetEquipmentComp()->GetArmorActor()->GetItemInfo<FIteminfo>()->itemActorClass);
	GetGameInstance<UMyGameInstance>()->SetTool(player->GetToolComp()->GetToolActor()->GetItemInfo<FIteminfo>()->itemActorClass);

	for(auto iter : player->GetSkillComp()->GetSkills())
	{
		GetGameInstance<UMyGameInstance>()->SetSkill(Cast<ASkillBaseActor>(iter)->GetSkillInfo<FSkill>()->skillActorClass);
	}

	GetGameInstance<UMyGameInstance>()->SetStat(player->GetStatusComponent()->GetCharacterStat());

	UGameplayStatics::OpenLevel(this, "Demonstration");

}
