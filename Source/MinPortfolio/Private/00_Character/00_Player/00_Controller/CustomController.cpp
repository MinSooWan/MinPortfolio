// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/00_Controller/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Widget/MainWidget.h"
#include "00_Character/99_Component/ToolComponent.h"
#include "01_Item/ItemActor.h"
#include "00_Character/99_Component/EquipmentComponent.h"

void ACustomController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	APlayerCharacter* player = Cast<APlayerCharacter>(aPawn);
	UE_LOG(LogTemp, Log, TEXT("000"));
	if (player != nullptr) {

		UE_LOG(LogTemp, Log, TEXT("111"));
		mainWidget = CreateWidget<UMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr) {
			UE_LOG(LogTemp, Log, TEXT("222"));
			player->GetToolComp()->ToolCompInit();
			player->GetEquipmentComp()->EquipmentCompInit();

			mainWidget->AddToViewport();
		}
	}
}
